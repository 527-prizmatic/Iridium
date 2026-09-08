#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/text.hpp"

#include "Iridium/vgui/element.hpp"
#include "Iridium/vgui/checkbox.hpp"
#include "Iridium/vgui/label.hpp"
#include "Iridium/vgui/input_field.hpp"
#include "Iridium/vgui/slider.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() {
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			auto code = event.getIf<sf::Event::KeyReleased>()->code;
			if (code == sf::Keyboard::Key::Escape) {
				meta_exit();
			}
		}
	}

	void onUpdate() { }

	void onRender() { }
		
	void onEnd() { }

private:
};

#endif // PROJECT_TESTSTATE_HPP_