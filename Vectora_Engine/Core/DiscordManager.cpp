#define DISCORDPP_IMPLEMENTATION
#include "DiscordManager.h"	
#include "vpch.h"

namespace Vectora {
	DiscordManager::DiscordManager()
	{
	}
	DiscordManager::~DiscordManager()
	{

	}
	void DiscordManager::Init()
	{
		s_Client = CreateRef<discordpp::Client>();
		s_Client->SetApplicationId(application_id);

		s_Client->AddLogCallback([](auto message, auto severity) {
			std::cout << "[" << EnumToString(severity) << "] " << message << std::endl;
			}, discordpp::LoggingSeverity::Info);

		s_Client->SetStatusChangedCallback([](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
			if (status == discordpp::Client::Status::Ready) {
				VE_CORE_INFO("Discord: Client is ready!");
				s_IsReady = true;

				// Set initial status once ready
				UpdatePresence("Vectora Engine", "Idle");
			}
			else if (error != discordpp::Client::Error::None) {
				VE_CORE_ERROR("Discord Error: {0}", (int)error);
			}
			});

		
		//s_Client->Connect();
	}
	void DiscordManager::ShutDown()
	{
	}
	void DiscordManager::Update()
	{
		discordpp::RunCallbacks();
	}
	void DiscordManager::UpdatePresence(const std::string& details, const std::string& state, bool isPlaying)
	{
		if (!s_IsReady || !s_Client) return;
		// Configure rich presence details
		discordpp::Activity activity;
		activity.SetType(discordpp::ActivityTypes::Playing);
		activity.SetState(state);
		activity.SetDetails(details);

		s_Client->UpdateRichPresence(
			activity, [](const discordpp::ClientResult& result) {
				if (result.Successful()) {
					std::cout << "🎮 Rich Presence updated successfully!\n";
				}
				else {
					std::cerr << "❌ Rich Presence update failed";
				}
			});
	}
}
