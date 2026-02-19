#include "vpch.h"
#include "Core/Window.h"

#ifdef VE_PLATFORM_WINDOWS
#include "platforms/Windows/WindowsWindow.h"
#endif

namespace Vectora
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef VE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		VE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}