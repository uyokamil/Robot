// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

using UnrealBuildTool;

public class Robot : ModuleRules
{
	public Robot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"AIModule",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks"
        });
    }
}
