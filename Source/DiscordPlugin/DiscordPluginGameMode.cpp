// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiscordPluginGameMode.h"
#include "DiscordPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiscordPluginGameMode::ADiscordPluginGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
