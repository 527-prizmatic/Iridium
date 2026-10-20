#ifndef PROJECT_STATE_ENTRY_HPP_
#define PROJECT_STATE_ENTRY_HPP_

#include "state.hpp"
#include "rendering/text.hpp"
#include "dev_utils.hpp"

class EntryState : public ir::StateBase<EntryState> {
public:
	void onInitialize() {
		text_ = std::make_unique<ir::render::Text>("abcdefghijklmnopqrstuvwxyz abcdefghijklmnopqrstuvwxyz");
		text_->setColor(sf::Color::Green)
			.setScale(15.f);
	}

	void onReceiveEvent(const sf::Event& event) { }

	void onUpdate() { }

	void onRender() {
		ir::time([&]() {
			for (int i = 0; i < 200; i++) {
				text_->setPosition(ir::Vector { 10.f, 10.f + i * 5.f });
				text_->render(*context_->vertexRenderer);
			}
		}, "Text rendering");
	}

	void onEnd() { }

private:
	std::unique_ptr<ir::render::Text> text_;
};

#endif // PROJECT_STATE_ENTRY_HPP_