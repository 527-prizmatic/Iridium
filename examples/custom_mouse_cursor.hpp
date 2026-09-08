#ifndef PROJECT_MY_STATE_HPP_
#define PROJECT_MY_STATE_HPP_

#include "state.hpp"
#include "rendering/circle.hpp"

class MyState : public ir::StateBase<MyState> {
public:
	void onInitialize() {
		context_->appWindow->enableMouseCursor(false);
		circle_ = std::make_unique<ir::render::Circle>();
		if (circle_) {
			circle_->setMode(ir::render::Mode::WIREFRAME); ///< Choose between outlines (wireframe) or surfaces (solid)
			circle_->setRadius(10.f);
			circle_->setColor(sf::Color { 128u, 255u, 255u }); ///< These functions use sf::Color for now, implementations for ir::RGBColor and ir::HSLColor coming soon
		}
	}

	void onReceiveEvent(const sf::Event& event) { }

	void onUpdate() {
		if (circle_) {
			circle_->setPosition(context_->mouseInput->getCursorPosition());
		}
	}

	void onRender() {
		if (circle_) {
			/// You always pass the renderer to shapes--not the other way around.
			circle_->render(*context_->vertexRenderer);
		}
	}
		
	void onEnd() {
		/// Note that states are not destroyed when unloaded, so you should always destroy resources manually for now.
		/// (This may come in future versions.)
		circle_.reset();
	}

private:
	/// I heavily recommend the use of unique pointers for simplifying memory management.
	std::unique_ptr<ir::render::Circle> circle_;
};

#endif // PROJECT_MY_STATE_HPP_