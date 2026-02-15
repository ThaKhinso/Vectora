#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "platforms/OpenGL/OpenGLShader.h"

namespace Vectora {
	Ref<Shader> Shader::Create(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexShaderPath, fragmentShaderPath);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexShaderPath, fragmentShaderPath);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(unsigned int vertexShaderID, unsigned int fragmentShaderID)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexShaderID, fragmentShaderID);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(std::string vertexShaderPath, unsigned int fragmentShaderID)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexShaderPath, fragmentShaderID);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(unsigned int vertexShaderID, std::string fragmentShaderPath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererApi::None is currently unsupported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return make_shared<OpenGLShader>(vertexShaderID, fragmentShaderPath);
		default:
			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		VE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	//Shader Library implet
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		VE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Vectora::Ref<Vectora::Shader> ShaderLibrary::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto shader = Shader::Create(vertexPath, fragmentPath);
		Add(shader);
		return shader;
	}

	Vectora::Ref<Vectora::Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto shader = Shader::Create(name, vertexPath, fragmentPath);
		Add(name, shader);
		return shader;
	}

	Vectora::Ref<Vectora::Shader> ShaderLibrary::Get(const std::string& name)
	{
		VE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}