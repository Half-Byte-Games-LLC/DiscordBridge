// Copyright Half Byte Games LLC. All Rights Reserved 2024

#pragma once

#include "CoreMinimal.h"
#include "DiscordBridge/Thirdparty/discord_files/discord.h"  // Discord SDK include
#include "Components/ActorComponent.h"
#include "DiscordRichPresenceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DISCORDBRIDGE_API UDiscordRichPresenceComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	UDiscordRichPresenceComponent();

	// Function to update Discord Rich Presence
	UFUNCTION(BlueprintCallable, Category = "Discord")
	void UpdateRichPresence(FString State, FString Details);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	discord::Core* DiscordCore;  // Discord SDK Core object
};
