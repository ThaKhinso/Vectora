#include "vpch.h"
#include "ScriptEngine.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"

namespace Vectora {

	struct ScriptEngineData {
		MonoDomain* RootData = nullptr;
	};

	static ScriptEngineData* s_Data;

	void ScriptEngine::Init()
	{
		InitMono();
		s_Data = new ScriptEngineData();

	}
	void ScriptEngine::Shutdown()
	{
		delete s_Data;
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("mono");

		MonoDomain* rootDomain = mono_jit_init("MyScriptRuntime");
		VE_CORE_ASSERT(rootDomain);

		// Store the root domain pointer
		s_Data->RootData = rootDomain;


	}
}