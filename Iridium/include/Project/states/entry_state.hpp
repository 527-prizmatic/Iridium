#ifndef PROJECT_STATE_ENTRY_HPP_
#define PROJECT_STATE_ENTRY_HPP_

#include "state.hpp"
#include "rendering/text.hpp"
#include "dev_utils.hpp"

class EntryState : public ir::StateBase<EntryState> {
public:
	void onInitialize() {
		text_.create("abcdefghijklmnopqrstuvwxyz abcdefghijklmnopqrstuvwxyz")
			->setColor(sf::Color::Green)
			.setScale(15.f)
			.setMode(ir::render::Mode::WIREFRAME);

		auto handle = context_->assetManager->registerModel("tools\\cross.vmf");
		context_->assetManager->deleteModel(handle);
	}

	void onReceiveEvent(const sf::Event& event) {
	}

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
	ir::LazyPointer<ir::render::Text> text_;
};

#endif // PROJECT_STATE_ENTRY_HPP_