#include "rendering/model_renderer.hpp"
#include "rendering/vertex_renderer.hpp"

namespace ir::render {
	ModelRenderer::ModelRenderer() : Shape() {
		renderingCache_ = std::make_unique<ir::render::Model>();
		mode_ = ir::render::Mode::SOLID;
	}

	void ModelRenderer::render(ir::render::VertexRenderer& renderer) const {
		if (!renderingCache_ || cacheCounter_ < 0) {
			directRender(renderer);
		}
		else {
			if (cacheCounter_ == 0) {
				regenerateCache();
			}
			cachedRender(renderer);
		}
		if (cacheCounter_ <= 0) {
			cacheCounter_++;
		}
	}

	Vertex ModelRenderer::transformVertex(const Vertex &v) const {
		ir::Vector position { static_cast<float>(v.x), static_cast<float>(v.y) };
		position = position.rotate(angle_) * scale_;
		position += position_ - anchor_;
		
		return Vertex { static_cast<short int>(position.x), static_cast<short int>(position.y), v.color * color_ };
	}

	void ModelRenderer::regenerateCache() const {
		if (renderingCache_) {
			Model m;
			renderingCache_->clear();
			for (auto& cmp : model_) {
				ir::render::Component cmpTransformed { cmp };
				for (auto& v : cmpTransformed) {
					v = transformVertex(v);
				}
				renderingCache_->addComponent(cmpTransformed);
			}
		}
		else {
			LOG_WARN("Attempted to regenerate invalid VMF model cache!");
		}
	}

	void ModelRenderer::directRender(ir::render::VertexRenderer& renderer) const {
		/// Caches the previous component type to enable batch rendering whenever possible
		Component::Type prevType { Component::Type::POINT };

		renderer.reset(sf::PrimitiveType::Points);
		for (auto& cmp : model_) {
			if (cmp.type == Component::Type::POINT && mode_ == Mode::SOLID) {
				if (prevType != Component::Type::POINT) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Points);
				}
				addVertexToBuffer(transformVertex(cmp.vertices[0]), renderer);

				prevType = cmp.type;

			} else if (cmp.type == Component::Type::LINE) {
				if (prevType != Component::Type::LINE) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Lines);
				}
				addVertexToBuffer(transformVertex(cmp.vertices[0]), renderer);
				addVertexToBuffer(transformVertex(cmp.vertices[1]), renderer);

				prevType = cmp.type;

			} else if (cmp.type == Component::Type::TRIANGLE && mode_ == Mode::SOLID) {
				if (prevType != Component::Type::TRIANGLE) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Triangles);
				}
				addVertexToBuffer(transformVertex(cmp.vertices[0]), renderer);
				addVertexToBuffer(transformVertex(cmp.vertices[1]), renderer);
				addVertexToBuffer(transformVertex(cmp.vertices[2]), renderer);

				prevType = cmp.type;
			}
		}
		renderer.flush();
	}

	void ModelRenderer::cachedRender(ir::render::VertexRenderer& renderer) const {
		/// Caches the previous component type to enable batch rendering whenever possible
		Component::Type prevType { Component::Type::POINT };

		renderer.reset(sf::PrimitiveType::Points);
		for (auto& cmp : *renderingCache_) {
			if (cmp.type == Component::Type::POINT && mode_ == Mode::SOLID) {
				if (prevType != Component::Type::POINT) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Points);
				}
				addVertexToBuffer(cmp.vertices[0], renderer);

				prevType = cmp.type;

			} else if (cmp.type == Component::Type::LINE) {
				if (prevType != Component::Type::LINE) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Lines);
				}
				addVertexToBuffer(cmp.vertices[0], renderer);
				addVertexToBuffer(cmp.vertices[1], renderer);

				prevType = cmp.type;

			} else if (cmp.type == Component::Type::TRIANGLE && mode_ == Mode::SOLID) {
				if (prevType != Component::Type::TRIANGLE) {
					renderer.flush();
					renderer.reset(sf::PrimitiveType::Triangles);
				}
				addVertexToBuffer(cmp.vertices[0], renderer);
				addVertexToBuffer(cmp.vertices[1], renderer);
				addVertexToBuffer(cmp.vertices[2], renderer);

				prevType = cmp.type;
			}
		}
		renderer.flush();
	}
	
	void ModelRenderer::addVertexToBuffer(const Vertex &v, ir::render::VertexRenderer& renderer) const {
		renderer.addPoint(ir::Vector { static_cast<float>(v.x), static_cast<float>(v.y) }, v.color);
	}
	
	void ModelRenderer::addVertexToBuffer(ir::Vector pos, sf::Color clr, ir::render::VertexRenderer& renderer) const {
		renderer.addPoint(pos, clr);
	}

	ir::Vector ModelRenderer::boundingBoxSize() {
		ir::Vector posMin { 0.f, 0.f };
		ir::Vector posMax { 0.f, 0.f };
		for (auto& cmp : model_) {
			for (auto& v : cmp) {
				posMin.x = ir::math::min(static_cast<short>(posMin.x), v.x);
				posMin.y = ir::math::min(static_cast<short>(posMin.y), v.y);
				posMax.x = ir::math::max(static_cast<short>(posMax.x), v.x);
				posMax.y = ir::math::max(static_cast<short>(posMax.y), v.y);
			}
		}

		return (posMax - posMin) * scale_;
	}

	ModelRenderer& ModelRenderer::setScale(float scale) {
		scale_ = scale;
		resetCacheCounter();
		return *this;
	}

	ModelRenderer& ModelRenderer::setModel(Model& model) {
		model_ = model;
		resetCacheCounter();
		return *this;
	}

	ModelRenderer& ModelRenderer::setModel(Model&& model) {
		model_ = std::move(model);
		resetCacheCounter();
		return *this;
	}
}