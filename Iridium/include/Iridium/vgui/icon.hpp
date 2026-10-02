#ifndef IRIDIUM_VGUI_ICON_HPP_
#define IRIDIUM_VGUI_ICON_HPP_

#include "vgui/element.hpp"
#include <string>

namespace ir {
	namespace render {
		class ModelRenderer;
	}

	namespace vgui {
		/// @brief VGUI element for rendering VMF models as UI icons.
		/// @note Icons block updates, and do not prevent their parent from updating.
		class Icon : public Element {
		public:
			Icon();
			Icon(std::filesystem::path filename);
			Icon(ir::render::Model model);

			virtual bool update(ir::input::Mouse& mouse) override;
			virtual void render(ir::render::VertexRenderer& renderer) const override;

			ir::vgui::Icon& setScale(float scale);
			[[nodiscard]] inline float scale() const { return scale_; }

			ir::vgui::Icon& setIcon(std::filesystem::path text);
			ir::vgui::Icon& setIcon(ir::render::Model model);

		private:
			std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;

			float scale_ { 25.f };
		};
	}
}

#endif // IRIDIUM_VGUI_ICON_HPP_