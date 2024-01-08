#ifndef CARCONSOLE_CXX
#define CARCONSOLE_CXX

#pragma once

#include <memory>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/loop.hpp> // ftxui::Loop

#include <nod/nod.hpp>

#include "../system/CarSystem.h"

using namespace car::system;
using namespace ftxui;

namespace car::display {
	static const ButtonOption animated_button_style = ButtonOption::Animated();
	class CarConsole
	{
	public:
		inline Component MainComponent(Component main_button, std::function<void()> show_exit_modal) {
			auto component = Container::Vertical({
				main_button,
				Button("Quit", show_exit_modal, animated_button_style),
				});
			// Polish how the two buttons are rendered:
			component |= Renderer([&](Element inner) {
				return vbox({
						   text("Main component"),
						   separator(),
						   inner,
					})                                //
					| size(WIDTH, GREATER_THAN, 15)   //
					| size(HEIGHT, GREATER_THAN, 15)  //
					| border                          //
					| center;                         //
				});
			return component;
		}

		inline Component ExitModalComponent(std::function<void()> hide_exit_modal,
			std::function<void()> exit) {
			auto component = Container::Vertical({
				Button("No", hide_exit_modal, animated_button_style),
				Button("Yes", exit, animated_button_style),
				});
			// Polish how the two buttons are rendered:
			component |= Renderer([&](Element inner) {
				return vbox({
						   text("Are you sure you want to exit?"),
						   separator(),
						   inner,
					})                               //
					| size(WIDTH, GREATER_THAN, 30)  //
					| border;                        //
				});
			return component;
		}

		CarConsole(std::unique_ptr<CarSystem> car_system) : car_system(std::move(car_system)) {
		};

		void run() {
			auto screen = ScreenInteractive::Fullscreen();

			// State of the ExitModalComponent:
			bool exit_modal_shown = false;

			auto show_exit_modal = [&] { exit_modal_shown = true; };
			auto hide_exit_modal = [&] { exit_modal_shown = false; };

			bool debounce = false;
			bool button_pressed = false;
			std::string main_button_text = "Start Car Application";

			auto main_button_lambda = [&] {
				if (debounce) return;
				debounce = true;
				button_pressed = !button_pressed;
				std::cout << "Button pressed: " << button_pressed << std::endl;
				if (button_pressed) {
					main_button_text = "Connecting...";
					this->car_system->start();
					main_button_text = "Stop Car Application";
				}
				else {
					main_button_text = "Disconnecting...";
					this->car_system->stop();
					main_button_text = "Start Car Application";
				}
				debounce = false;
				};

			auto main_button = Button(&main_button_text, main_button_lambda, animated_button_style);

			auto exit = screen.ExitLoopClosure();

			auto main_component = MainComponent(main_button, show_exit_modal);
			auto modal_component = ExitModalComponent(hide_exit_modal, exit);
			main_component |= Modal(modal_component, &exit_modal_shown);

			auto renderer_line_block = Renderer([&] {
				auto c = Canvas(100, 100);
				for (auto& point : this->car_system->get_scan_data()) {
					const double angle = point.angle;
					const double distance = point.distance;
					const double angleInRadians = angle * (3.14159265f / 180.0f);
					const int x = distance * std::cos(angleInRadians);
					const int y = distance * std::sin(angleInRadians);
					c.DrawBlockLine(50, 50, x, y, Color::Blue);
				}
				return canvas(std::move(c));
				}
			);


			nod::signal<void(bool)> lidar_signal;

			bool loading = false;
			std::string lidar_status = "Lidar Status: Disconnected";
			bool lidar_enabled = false;
			auto lidar_checkbox_option = CheckboxOption::Simple();
			lidar_checkbox_option.on_change = [&]
				{
					if (loading) {
						lidar_enabled = !lidar_enabled;
						return;
					}
					loading = true;
					if (lidar_enabled) {
						lidar_status = "Lidar Status: Connecting...";
					}
					else {
						lidar_status = "Lidar Status: Disconnecting...";
					}
					lidar_signal(lidar_enabled);
				};
			auto lidar_checkbox = Checkbox(&lidar_status, &lidar_enabled, lidar_checkbox_option);

			int image_index = 0;
			auto lidar_spinner = Renderer([&] {return spinner(18, image_index); });
			auto settings_container = Container::Vertical({
				lidar_checkbox,
				Maybe(lidar_spinner, &loading),
				}
			);

			int selected_tab = 0;
			std::vector<std::string> tab_titles = {
				"Main",
				"Scan Map",
				"Settings",
			};

			auto tab_selection = Toggle(&tab_titles, &selected_tab);

			auto tab_content = Container::Tab(
				{
					main_component,
					renderer_line_block,
					settings_container,
				}
				, &selected_tab
			);

			auto main_container = Container::Vertical(
				{
				tab_selection,
				tab_content,
				}
			);

			auto main_renderer = Renderer(main_container, [&]
				{
					return vbox({
						text("Car Application") | bold | hcenter,
						tab_selection->Render(),
						tab_content->Render() | flex,
						}
					);
				}
			);

			this->car_system->initialize();

			lidar_signal.connect([&](bool connected)
				{
					if (connected) {
						this->car_system->start_lidar_device();
						lidar_status = "Lidar Status: Connected";
						loading = false;
					}
					else {
						this->car_system->stop_lidar_device();
						lidar_status = "Lidar Status: Disconnected";
						loading = false;
					}
				}
			);

			std::atomic<bool> refresh_ui_continue = true;
			std::thread refresh_ui([&]
				{
					while (refresh_ui_continue) {
						using namespace std::chrono_literals;
						std::this_thread::sleep_for(0.05s);
						// The |shift| variable belong to the main thread. `screen.Post(task)`
						// will execute the update on the thread where |screen| lives (e.g. the
						// main thread). Using `screen.Post(task)` is threadsafe.
						screen.Post([&] { image_index++; });
						// After updating the state, request a new frame to be drawn. This is done
						// by simulating a new "custom" event to be handled.
						screen.Post(Event::Custom);
					}
				}
			);

			screen.Loop(main_renderer);

			this->car_system->stop();
		};

	private:
		std::unique_ptr<CarSystem> car_system;
	};
}

#endif