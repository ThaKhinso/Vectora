#include "Application.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Log.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


namespace Vectora {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication | EventCategoryMouse)) {

			V_TRACE(e);
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			V_TRACE(e);
		}

		while (true);
	}

	
}