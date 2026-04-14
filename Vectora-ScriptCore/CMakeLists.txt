# Enable C# support
project(Vectora-ScriptCore LANGUAGES CSharp)

# Set the .NET SDK style (Modern way)
set(CMAKE_DOTNET_SDK "Microsoft.NET.Sdk")

# Sources
file(GLOB_RECURSE SOURCES "*.cs")

# Create the assembly (Library)
add_library(Vectora-ScriptCore SHARED ${SOURCES})

# Specify target framework (Mono works best with net472 or netstandard2.0)
set_property(TARGET Vectora-ScriptCore PROPERTY DOTNET_TARGET_FRAMEWORK "net472")
set_target_properties(Vectora-ScriptCore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
)