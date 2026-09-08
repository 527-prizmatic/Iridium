#ifndef PROJECT_MYDRAWABLE_HPP_
#define PROJECT_MYDRAWABLE_HPP_

#include "rendering/vertex_renderer.hpp"

class MyDrawable : public ir::render::Shape {
public:
	inline void render(ir::render::VertexRenderer& renderer) const {
		/// Clears renderer buffer
		renderer.reset(sf::PrimitiveType::LineStrip);

		/// Add points to renderer buffer
		renderer.addPoint(position_ + ir::Vector { -50.f, 0.f }, color_); /// position_ and color_ are native ir::render::Shape properties
		renderer.addPoint(position_ + ir::Vector { 0.f, 50.f }, color_);
		renderer.addPoint(position_ + ir::Vector { 50.f, 0.f }, color_);
		renderer.addPoint(position_ + ir::Vector { 0.f, -50.f }, color_);
		renderer.addPoint(position_ + ir::Vector { -50.f, 0.f }, color_); ///< Always close shapes if drawing lines!

		/// Flush renderer buffer to screen
		renderer.flush();
	}
};

#endif // PROJECT_MYDRAWABLE_HPP_