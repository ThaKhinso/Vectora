#include "platforms/OpenGL/OpenGLShader.h"
#include "Debug/Instrumentor.h"
#include <glm/gtc/type_ptr.hpp>

namespace Vectora {
	void OpenGLShader::getShaderCompilationError(unsigned int shaderID, GLenum ERROR_TYPE, ShaderType type) {
		int success;
		char log[512];
		std::string stype;
		if (type == VERTEX) {
			stype = "VERTEX";
		}
		else {
			stype = "FRAGMENT";
		}
		glGetShaderiv(shaderID, ERROR_TYPE, &success);

		if (!success) {
			glGetShaderInfoLog(shaderID, sizeof(log), NULL, log);
			printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s", stype.c_str(), log);
		}
	}

	void OpenGLShader::getShaderLinkError(unsigned int program, GLenum ERROR_TYPE) {
		int success;
		char log[512];
		glGetProgramiv(program, ERROR_TYPE, &success);

		if (!success) {
			glGetProgramInfoLog(program, sizeof(log), NULL, log);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", log);
		}
	}

	OpenGLShader::OpenGLShader(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		VE_PROFILE_FUNCTION();
		loadShaders(vertexShaderPath, fragmentShaderPath);
		createShaders(ShaderCreationMode::BOTH_FROM_FILE);

		// Extract name from filepath, this is done assuming that both vertex and fragment shaders 
		// have the same name and are in the same directory. This is not a requirement but just a convention.
		// this can crash if the vertex and fragment don't follow the same pattern
		// shaders should be named "named.type.glsl" for opengl shaders. like "Texture.vertex.glsl" for example
		auto lastSlash = vertexShaderPath.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
		auto firstDot = vertexShaderPath.find('.', lastSlash);
		auto count = (firstDot == std::string::npos)
			? vertexShaderPath.size() - lastSlash 
			: firstDot - lastSlash;
		m_Name = vertexShaderPath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, std::string vertexShaderPath, std::string fragmentShaderPath)
		:m_Name(name)
	{
		VE_PROFILE_FUNCTION();
		loadShaders(vertexShaderPath, fragmentShaderPath);
		createShaders(ShaderCreationMode::BOTH_FROM_FILE);
	}

	OpenGLShader::OpenGLShader(unsigned int vertexShaderID, unsigned int fragmentShaderID) {
		this->vertexShader = vertexShaderID;
		this->fragmentShader = fragmentShaderID;
	}

	OpenGLShader::OpenGLShader(std::string vertexShaderPath, unsigned int fragmentShaderID) {
		loadVertexShader(vertexShaderPath);
		this->fragmentShader = fragmentShaderID;
	}

	OpenGLShader::OpenGLShader(unsigned int vertexShaderID, std::string fragmentShaderPath) {
		this->vertexShader = vertexShaderID;
		loadFragmentShader(fragmentShaderPath);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(RenderID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::loadShaders(std::string vPath, std::string fPath) {
		loadVertexShader(vPath);
		loadFragmentShader(fPath);
	}

	void OpenGLShader::loadVertexShader(std::string vPath) {
		VE_PROFILE_FUNCTION();
		vertexShaderSource.clear();
		std::ifstream vShaderFile(vPath, std::ios::in | std::ios::binary);
		std::string line;
		if (vShaderFile) {
			std::stringstream vShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			vertexShaderSource = vShaderStream.str();
			vShaderFile.close();
			
		}
		else {
			VE_CORE_ERROR("Could not open file {0}", vPath);
		}
	}

	void OpenGLShader::loadFragmentShader(std::string fPath) {
		VE_PROFILE_FUNCTION();
		fragmentShaderSource.clear();
		std::ifstream fShaderFile(fPath, std::ios::in | std::ios::binary);
		std::string line;

		if (fShaderFile) {
			std::stringstream vShaderStream;
			vShaderStream << fShaderFile.rdbuf();
			fragmentShaderSource = vShaderStream.str();
			fShaderFile.close();
		}
		else {
			VE_CORE_ERROR("Could not open file {0}", fPath);
		}

	}

	void OpenGLShader::createShaders(ShaderCreationMode mode) {

		VE_PROFILE_FUNCTION();
		if (mode == ShaderCreationMode::BOTH_FROM_FILE)
		{
			this->compileVertexShader();
			compileFragmentShader();
			linkShaders();
		}
		else if (mode == ShaderCreationMode::BOTH_FROM_ID) {
			linkShaders();
		}
		else if (mode == ShaderCreationMode::VERTEX_ID_FRAG_FILE) {
			compileFragmentShader();
			linkShaders();
		}
		else if (mode == ShaderCreationMode::VERTEX_FILE_FRAG_ID) {
			compileVertexShader();
			linkShaders();
		}

	};

	void OpenGLShader::compileVertexShader() {
		VE_PROFILE_FUNCTION();
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSource = vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		getShaderCompilationError(vertexShader, GL_COMPILE_STATUS, VERTEX);
	}

	void OpenGLShader::compileFragmentShader() {
		VE_PROFILE_FUNCTION();
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragSource = fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &fragSource, NULL);
		glCompileShader(fragmentShader);
		getShaderCompilationError(fragmentShader, GL_COMPILE_STATUS, FRAGMENT);
	}

	void OpenGLShader::linkShaders() {
		VE_PROFILE_FUNCTION();
		RenderID = glCreateProgram();
		glAttachShader(RenderID, vertexShader);
		glAttachShader(RenderID, fragmentShader);
		glLinkProgram(RenderID);
		getShaderLinkError(RenderID, GL_LINK_STATUS);
	}

	void OpenGLShader::setFloat(const std::string& name, float value) const {
		VE_PROFILE_FUNCTION();
		glUniform1f(glGetUniformLocation(RenderID, name.c_str()), value);
	}

	void OpenGLShader::setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(RenderID, name.c_str()), value);
	}
	void OpenGLShader::setInt(const std::string& name, int value) const {
		VE_PROFILE_FUNCTION();
		glUniform1i(glGetUniformLocation(RenderID, name.c_str()), value);
	}

	void OpenGLShader::setVec2(const std::string& name, float v1, float v2) const {
		VE_PROFILE_FUNCTION();
		glUniform2f(glGetUniformLocation(RenderID, name.c_str()), v1, v2);
	}

	void OpenGLShader::setVec3(const std::string& name, const glm::vec3& vec4) const
	{
		VE_PROFILE_FUNCTION();
		glUniform3f(glGetUniformLocation(RenderID, name.c_str()), vec4.x, vec4.y, vec4.z);
	}

	void OpenGLShader::setVec4(const std::string& name, const glm::vec4& vec4) const
	{
		VE_PROFILE_FUNCTION();
		glUniform4f(glGetUniformLocation(RenderID, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
	}


	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& trans) const {
		VE_PROFILE_FUNCTION();
		glUniformMatrix4fv(glGetUniformLocation(RenderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count) const
	{
		VE_PROFILE_FUNCTION();
		GLint location = glGetUniformLocation(RenderID, name.c_str());
		glUniform1iv(location, count, values);
	}

}