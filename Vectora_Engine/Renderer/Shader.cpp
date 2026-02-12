#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "platforms/OpenGL/OpenGLShader.h"

namespace Vectora {
	Shader* Shader::Create(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexShaderPath, fragmentShaderPath);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	Shader* Shader::Create(unsigned int vertexShaderID, unsigned int fragmentShaderID)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexShaderID, fragmentShaderID);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	Shader* Shader::Create(std::string vertexShaderPath, unsigned int fragmentShaderID)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexShaderPath, fragmentShaderID);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	Shader* Shader::Create(unsigned int vertexShaderID, std::string fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexShaderID, fragmentShaderPath);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
}