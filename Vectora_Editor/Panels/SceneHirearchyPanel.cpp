#include "SceneHirearchyPanel.h"

#include "Scene/Components.h"

#include <imgui.h>

namespace Vectora {
	SceneHirearchyPanel::SceneHirearchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}
	void SceneHirearchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}
	void SceneHirearchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hirearchy");
		auto view = m_Context->m_Registry.view<entt::entity>();

		for (auto entityID : view)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		}
		ImGui::End();
	}
	void SceneHirearchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}
}
