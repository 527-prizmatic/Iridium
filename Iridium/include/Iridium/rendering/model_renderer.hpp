#ifndef IRIDIUM_RENDERING_MODEL_RENDERER_HPP_
#define IRIDIUM_RENDERING_MODEL_RENDERER_HPP_

#include "rendering/shape.hpp"
#include "rendering/model.hpp"

namespace ir::render {
	/// @brief Utility class for rendering VMF models.
	class ModelRenderer : public Shape {
	public:
		ModelRenderer();

		/// @brief Draws the object on the given render target.
		///
		/// `ir::render::ModelRenderer`'s version of this function dynamically caches rendering data
		/// after a certain number of calls since last cache invalidation (stored in `ir::render::Shape::kCacheReset`).
		virtual void render(ir::render::VertexRenderer& renderer) const;	

		ModelRenderer& setModel(Model& model);
		ModelRenderer& setModel(Model&& model);
		[[nodiscard]] Model& model() { return model_; }

		/// @attention At a scale of 1, one grid unit in the model corresponds to one screen pixel.
		virtual ModelRenderer& setScale(float scale);

		/// @attention At a scale of 1, one grid unit in the model corresponds to one screen pixel.
		[[nodiscard]] virtual float scale() const { return scale_; }

		[[nodiscard]] ir::Vector boundingBoxSize(); ///< @return Scale-adjusted size of the model's bounding box

	protected:
		float scale_ { 1.f };
		/// @todo Find a way to replace this with a reference or pointer
		/// This would require a solid memory management system though, to avoid leaks in case the renderer ever gains ownership of the model one way or another
		/// (Though ideally it should never do so)
		Model model_;
		std::unique_ptr<Model> renderingCache_;
		
		/// @brief Preemptively applies position and color transformations to the contents of `model_`
		/// and stores results in `renderingCache_`.
		void regenerateCache() const;

		virtual void directRender(ir::render::VertexRenderer& renderer) const; ///< Renders directly by recomputing vertex values at runtime
		virtual void cachedRender(ir::render::VertexRenderer& renderer) const; ///< Renders from cache

		virtual void addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const;
		virtual void addVertexToBuffer(ir::Vector pos, sf::Color clr, ir::render::VertexRenderer& renderer) const;

		Vertex transformVertex(const Vertex &v) const;
		
		std::unique_ptr<sf::VertexArray> vertexCache_;
	};
}





#endif