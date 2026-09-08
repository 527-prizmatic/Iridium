#ifndef PROJECT_STATE_ENTRY_HPP_
#define PROJECT_STATE_ENTRY_HPP_

#include "Iridium/state.hpp"

class EntryState : public ir::StateBase<EntryState> {
public:
	void onInitialize() { }
	
	void onReceiveEvent(const sf::Event& event) { }

	void onUpdate() { }

	void onRender() { }
		
	void onEnd() { }

private:
};

#endif // PROJECT_STATE_ENTRY_HPP_