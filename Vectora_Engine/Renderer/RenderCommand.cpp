#include "RenderCommand.h"
#include "vpch.h"
#include "platforms/OpenGL/OpenGLRendererAPI.h"

namespace Vectora{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}