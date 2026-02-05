#pragma once

#include "Renderer/VertexArray.h"

namespace Vectora {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override final;
		virtual void Bind() const override final;
		virtual void UnBind() const override final;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override final;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override final;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override final;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override final;
	private:
		VE_UINT32 m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}