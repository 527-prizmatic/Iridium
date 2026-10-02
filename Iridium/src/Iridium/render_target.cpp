#include "render_target.hpp"

namespace ir {
	void RenderTarget::expectValid() {
		if (!isValid()) {
			throw ir::Exceptions::InvalidRenderTarget{};
		}
	}
}