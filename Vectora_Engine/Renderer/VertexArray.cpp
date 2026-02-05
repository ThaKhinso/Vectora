#include "VertexArray.h"
#include "Renderer.h"
#include "platforms/OpenGL/OpenGlVertexArray.h"

namespace Vectora {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}
	}
}