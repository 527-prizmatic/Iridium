#ifndef IRIDIUM_VGUI_LABEL_HPP_
#define IRIDIUM_VGUI_LABEL_HPP_

#include "vgui/element.hpp"
#include "rendering/text.hpp"

namespace ir {
	namespace render {
		class Text;
	}

	namespace vgui {
		/// @brief VGUI element for rendering VMF-based text as UI labels.
		/// @note Labels block updates, and do not prevent their parent from updating.
		class Label : public Element {
		public:
			enum class Anchor : unsigned char {
				NONE,
				LEFT,
				RIGHT,
				TOP,
				BOTTOM,
				OVER
			};

			Label(std::string text = "label");

			virtual bool update(ir::input::Mouse& mouse) override;
			virtual void render(ir::render::VertexRenderer& renderer) const override;

			ir::vgui::Label& setScale(float scale);
			float scale();

			ir::vgui::Label& setLabel(std::string text); ///< @brief Sets label text
			[[nodiscard]] std::string label() const; ///< @return Label text

			ir::vgui::Label& setColor(sf::Color clr); ///< @brief Sets label color
			[[nodiscard]] sf::Color color() const;

			ir::vgui::Label& setAnchor(Anchor anchor); ///< @brief Sets anchoring relative to the parent element
			[[nodiscard]] Anchor anchor() const; ///< @brief Anchoring relative to the parent element
			
			/// @brief Sets position relative to the parent (or the window if there is none)
			///
			/// If anchoring is set to anything other than Anchor::NONE, this function does nothing.
			virtual ir::vgui::Element& setPosition(ir::Vector pos) override;

		protected:
			std::unique_ptr<ir::render::Text> label_;
			Anchor anchor_ { Anchor::NONE };
		};
	}
}
	
#endif // IRIDIUM_VGUI_LABEL_HPP_