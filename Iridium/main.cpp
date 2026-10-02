#include "application.hpp"
#include "rendering/text.hpp"

#include <thread>

#if __has_include("states/entry_state.hpp")
	#include "states/entry_state.hpp"
#else
	#error entry_state.hpp not found. (Have you run IrSetup.exe?)
#endif

int main() {
	ir::log::startSession();
	try {
		std::thread thrText([&]() { ir::render::Text::loadModels(); });

		ir::Application app;
		app.initialize();
		thrText.join();

		app.run<EntryState>();
	}
	catch (...) {
		LOG_ERROR("Something terrible happened (caught unhandled exception, exiting)");
	}
	ir::log::endSession();
}