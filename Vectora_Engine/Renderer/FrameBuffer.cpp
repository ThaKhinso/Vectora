#include "vpch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"

#include "platforms/OpenGL/OpenGLFramebuffer.h"

namespace Vectora {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    VE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}