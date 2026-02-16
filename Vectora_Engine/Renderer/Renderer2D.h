#pragma once
#include "Renderer/OrthographiCamera.h"
#include "Texture.h"

namespace Vectora {
	class Renderer2D {
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthoGraphicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}