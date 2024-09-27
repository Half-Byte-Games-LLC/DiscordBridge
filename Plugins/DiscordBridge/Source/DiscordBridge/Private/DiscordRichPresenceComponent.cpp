// Copyright Half Byte Games LLC. All Rights Reserved 2024


#include "DiscordRichPresenceComponent.h"


// Sets default values for this component's properties
UDiscordRichPresenceComponent::UDiscordRichPresenceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DiscordCore = nullptr;  // Initialize the Discord Core pointer to null
}

void UDiscordRichPresenceComponent::UpdateRichPresence(FString State, FString Details)
{
	if (DiscordCore)
	{
		discord::Activity activity{};
		activity.SetState("In the Menu");    // Hardcoded test state
		activity.SetDetails("Exploring the Map"); // Hardcoded test details

		DiscordCore->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
			if (result == discord::Result::Ok)
			{
				UE_LOG(LogTemp, Log, TEXT("Discord Rich Presence updated successfully."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to update Discord Rich Presence."));
			}
		});
	}
}


// Called when the game starts
void UDiscordRichPresenceComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Discord Core with your Discord Client ID (replace with your actual Client ID)
	discord::Result result = discord::Core::Create(1285619199116578879, DiscordCreateFlags_Default, &DiscordCore);

	if (result == discord::Result::Ok && DiscordCore)
	{
		UE_LOG(LogTemp, Log, TEXT("Discord Core initialized successfully."));
		UpdateRichPresence("Hello", "World");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to initialize Discord Core."));
	}
}

void UDiscordRichPresenceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Run Discord callbacks to process SDK updates
	if (DiscordCore)
	{
		DiscordCore->RunCallbacks();
	}
}


