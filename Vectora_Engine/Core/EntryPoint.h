#pragma once
#ifdef VE_PLATFORM_WINDOWS
#include "Core/CmdArgumentHandler.h"
#include "Utils/PlatformUtils.h"
#include <filesystem>

extern Vectora::Application* Vectora::CreateApplication();

int main(int argc, char** argv) {
    
    Vectora::CmdArgumentHandler::Init(argc, argv);

    //fuck you windows, why tf you think force changing the working directory is a good idea.
    std::filesystem::current_path(Vectora::FileDialogs::GetExecutablePath());
    Vectora::Log::Init();
    
    VE_PROFILE_BEGIN_SESSION("Startup", "VectoraProfile-Startup.json");
    auto app = Vectora::CreateApplication();
    VE_PROFILE_END_SESSION();

    VE_PROFILE_BEGIN_SESSION("Runtime", "VectoraProfile-Runtime.json");
    app->Run();
    VE_PROFILE_END_SESSION();

    VE_PROFILE_BEGIN_SESSION("Shutdown", "VectoraProfile-Shutdown.json");
    delete app;
    VE_PROFILE_END_SESSION();
    return 0;
}
#endif