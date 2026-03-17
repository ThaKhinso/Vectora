#pragma once

#include "discordpp.h"

#include "Core/Core.h"
#include <string>

namespace Vectora
{
	class DiscordManager
	{
	public:
		DiscordManager();
		~DiscordManager();

		static void Init();
		static void ShutDown();
		static void Update();

		static void UpdatePresence(const std::string& details, const std::string& state, bool isPlaying = false);
	private:
		struct DiscordData {
			
		};
		inline static VE_UINT64 application_id = 1483295673691541656;
		inline static Ref<discordpp::Client> s_Client = nullptr;
		//inline static std::shared_ptr<discordpp::Client> s_Client = nullptr;
		inline static bool s_IsReady = false;
	};
}

