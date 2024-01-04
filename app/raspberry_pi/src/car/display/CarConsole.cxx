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
	static auto button_style = ButtonOption::Animated();
	class CarConsole
	{
	public:
		Component MainComponent(std::function<void()> show_exit_modal) {
			auto component = Container::Vertical({
				Button("Quit", show_exit_modal, button_style),
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

		Component ExitModalComponent(std::function<void()> hide_exit_modal,
			std::function<void()> exit) {
			auto component = Container::Vertical({
				Button("No", hide_exit_modal, button_style),
				Button("Yes", exit, button_style),
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
			auto exit = screen.ExitLoopClosure();

			auto main_component = MainComponent(show_exit_modal);
			auto modal_component = ExitModalComponent(hide_exit_modal, exit);
			main_component |= Modal(modal_component, &exit_modal_shown);

			Loop loop(&screen, main_component);

			this->car_system->initalize();
			this->car_system->start();
			// The main loop:
			while (!loop.HasQuitted()) {
				this->car_system->update();
				loop.RunOnce();
			}

			// Called after the loop ended.
			this->car_system->terminate();
		};

	private:
		std::unique_ptr<CarSystem> car_system;
	};
}

#endif