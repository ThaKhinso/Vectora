#include "vpch.h"
#include "ScriptGlue.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#define VE_ADD_INTERNAL_CALLS(Name) mono_add_internal_call("Vectora.InternalCalls::" #Name, (const void*)Name)

namespace Vectora {
	static void NativeLog(MonoString* text, int param) {
		char* cStr = mono_string_to_utf8(text);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << ", " << param << "\n";
	}

	static void NativeLogV3(glm::vec3* parameter) {
		VE_WARN("{0}", *parameter);
	}

	void ScriptGlue::RegisterFunctions()
	{
		VE_ADD_INTERNAL_CALLS(NativeLog);
		VE_ADD_INTERNAL_CALLS(NativeLogV3);
	}
}