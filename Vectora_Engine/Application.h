#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


namespace Vectora {
	class VECTORA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		bool OnWindowClosed(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}

