#ifndef CARCONSOLE_CXX
#define CARCONSOLE_CXX

#pragma once

#include <memory>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/loop.hpp> // ftxui::Loop

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

			Loop loop(&screen, main_component);

			this->car_system->initialize();

			// The main loop:
			while (!loop.HasQuitted()) {
				this->car_system->update();
				loop.RunOnce();
			}

			// Called after the loop ended.
			this->car_system->stop();
		};

	private:
		std::unique_ptr<CarSystem> car_system;
	};
}

#endif