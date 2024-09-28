using System.IO;
using UnrealBuildTool;

public class DiscordBridge : ModuleRules
{
    public DiscordBridge(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Define the absolute path to the Discord SDK files
        string DiscordFilesPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/discord_game_sdk/cpp"));
        
        // Add the absolute path to the include directory for Discord SDK
        PublicIncludePaths.Add(Path.Combine(DiscordFilesPath));

        // Determine platform-specific binary folder and set absolute paths
        string BinariesPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries"));
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string DiscordLibPath = Path.Combine(BinariesPath, "Win64", "discord_game_sdk.dll.lib");
            string DiscordDllPath = Path.Combine(BinariesPath, "Win64", "discord_game_sdk.dll");

            // Add the absolute path to the Discord SDK library
            PublicAdditionalLibraries.Add(DiscordLibPath);

            // Ensure the .dll is treated as a runtime dependency (so it's packaged correctly)
            RuntimeDependencies.Add(DiscordDllPath);
        }
        
        // Standard Unreal Engine dependency setup
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Slate", "SlateCore","DeveloperSettings"  });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
