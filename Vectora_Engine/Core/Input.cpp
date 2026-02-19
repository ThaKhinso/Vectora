#include "vpch.h"
#include "Core/Input.h"

#ifdef VE_PLATFORM_WINDOWS
#include "platforms/Windows/WindowsInput.h"
#endif

namespace Vectora {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef VE_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		VE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}