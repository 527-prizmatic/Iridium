#include "application.hpp"
#include <thread>

namespace ir {
	void Application::initialize() {
		try {
			std::thread t1 ([&]() {
				initializeComponent(gameClock_);
				gameClock_->zero();

				initializeComponent(mouse_);
				initializeComponent(keyboard_);

				initializeComponent(assetManager_);
				initializeComponent(soundManager_, assetManager_.address());

				initializeComponent(stateMachine_);

				initializeComponent(appState_);
				
				context_.gameClock = gameClock_.address();
				context_.mouse = mouse_.address();
				context_.keyboard = keyboard_.address();
				context_.assetManager = assetManager_.address();
				context_.soundManager = soundManager_.address();
				context_.appState = appState_.address();
			});
		
			initializeComponent(appWindow_, ir::Vector{ 1280.f, 720.f });
			appWindow_->setFPS(60u);
			initializeComponent(vertexRenderer_, appWindow_.address());
			t1.join();

			context_.appWindow = appWindow_.address();
			context_.vertexRenderer = vertexRenderer_.address();
			
			stateMachine_->registerContext(&context_);
		}
		catch (...) {
			throw nullptr; /// Replace with a real exc
		}

		expectInitialized();
		initialized_ = true;
	}

	void Application::runMainLoop() {
		expectInitialized();
		Expects(initialized_ == true);

		while (!stateMachine_->hasRequestedExit()) {
			gameClock_->startTick();
			appWindow_->reduceBackgroundResourceUsage();
			mouse_->update(appWindow_.value());
			keyboard_->update(appWindow_.value());

			/// Keep StateMachine init last
			stateMachine_->initialize();
			stateMachine_->handleEvents();
			stateMachine_->update();
			stateMachine_->render();

			soundManager_->update();
		}

		stateMachine_->unload();
	}

	void Application::expectInitialized() {
		Expects(appWindow_);
		Expects(vertexRenderer_);
		Expects(gameClock_);
		Expects(mouse_);
		Expects(keyboard_);
		Expects(stateMachine_);
		Expects(assetManager_);
		Expects(soundManager_);
	}
}