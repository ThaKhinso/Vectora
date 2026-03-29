#pragma once
#include <filesystem>

#include "Renderer/Texture.h"

namespace Vectora {
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_DirectoryIcon;
	};
}

