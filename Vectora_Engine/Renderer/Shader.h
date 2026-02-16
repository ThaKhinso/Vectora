#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>

namespace Vectora {
	enum ShaderType {
		VERTEX,
		FRAGMENT
	};

	enum ShaderCreationMode {
		BOTH_FROM_FILE,
		BOTH_FROM_ID,
		VERTEX_ID_FRAG_FILE,
		VERTEX_FILE_FRAG_ID
	};

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void setInt(const std::string& name, int value) const = 0;
		virtual void setFloat(const std::string& name, float value) const = 0;
		virtual void setVec2(const std::string& name, float v1, float v2) const = 0;
		virtual void setVec3(const std::string& name, const glm::vec3& vec4) const = 0;
		virtual void setVec4(const std::string& name, const glm::vec4& vec4) const = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& trans) const = 0;

		virtual void createShaders(ShaderCreationMode mode) = 0;
		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(std::string vertexShaderPath, std::string fragmentShaderPath);
		static Ref<Shader> Create(const std::string& name, std::string vertexShaderPath, std::string fragmentShaderPath);
		static Ref<Shader> Create(unsigned int vertexShaderID, unsigned int fragmentShaderID);
		static Ref<Shader> Create(std::string vertexShaderPath, unsigned int fragmentShaderID);
		static Ref<Shader> Create(unsigned int vertexShaderID, std::string fragmentShaderPath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& vertexPath, const std::string& fragmentPath);
		Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}