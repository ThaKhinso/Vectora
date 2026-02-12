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

		virtual void createShaders(ShaderCreationMode mode) = 0;
		virtual void useProgram() const = 0;

		static Shader* Create(std::string vertexShaderPath, std::string fragmentShaderPath);
		static Shader* Create(unsigned int vertexShaderID, unsigned int fragmentShaderID);
		static Shader* Create(std::string vertexShaderPath, unsigned int fragmentShaderID);
		static Shader* Create(unsigned int vertexShaderID, std::string fragmentShaderPath);
	};
}