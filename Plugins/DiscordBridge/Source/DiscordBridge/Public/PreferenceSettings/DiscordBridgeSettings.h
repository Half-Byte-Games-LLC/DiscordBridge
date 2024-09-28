// Copyright Half Byte Games LLC. All Rights Reserved 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DiscordBridgeSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Discord Bridge Settings"))
class DISCORDBRIDGE_API UDiscordBridgeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UDiscordBridgeSettings();
	
	// App Client ID that developers can set in the preferences
	UPROPERTY(EditAnywhere, config, Category = "Discord Settings", meta = (DisplayName = "Discord App Client ID"))
	FString AppClientID;
};
