#include "Renderer.h"
#include "vpch.h"


namespace Vectora {
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;
	void Renderer::BeginScence(OrthoGraphicCamera& camera)
	{
		sceneData->ViewProjectionMatrix = camera.GetPV();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->setMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);
		shader->setMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
