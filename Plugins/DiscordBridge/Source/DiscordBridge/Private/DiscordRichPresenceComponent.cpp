// Copyright Half Byte Games LLC. All Rights Reserved 2024


#include "DiscordRichPresenceComponent.h"

#include "PreferenceSettings/DiscordBridgeSettings.h"


// Sets default values for this component's properties
UDiscordRichPresenceComponent::UDiscordRichPresenceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DiscordCore = nullptr;  // Initialize the Discord Core pointer to null
}

void UDiscordRichPresenceComponent::UpdateRichPresence(FString State, FString Details, FString LargeImageKey, FString LargeImageText, FString SmallImageKey, FString SmallImageText, int32 PartySize, int32 MaxPartySize, FString PartyId, FString JoinSecret, FString SpectateSecret, bool bIsInstance)
{
    if (DiscordCore)
    {
        discord::Activity activity{};

        // Set state and details
        activity.SetState(TCHAR_TO_ANSI(*State));
        activity.SetDetails(TCHAR_TO_ANSI(*Details));

        // Set timestamps for start (example: current time)
        activity.GetTimestamps().SetStart(FDateTime::UtcNow().ToUnixTimestamp());

        // Set large image key and text
        activity.GetAssets().SetLargeImage(TCHAR_TO_ANSI(*LargeImageKey));
        activity.GetAssets().SetLargeText(TCHAR_TO_ANSI(*LargeImageText));

        // Set small image key and text
        activity.GetAssets().SetSmallImage(TCHAR_TO_ANSI(*SmallImageKey));
        activity.GetAssets().SetSmallText(TCHAR_TO_ANSI(*SmallImageText));

        // Set party information with Party ID
        if (PartySize > 0 && MaxPartySize > 0 && !PartyId.IsEmpty())
        {
            activity.GetParty().SetId(TCHAR_TO_ANSI(*PartyId));
            activity.GetParty().GetSize().SetCurrentSize(PartySize);
            activity.GetParty().GetSize().SetMaxSize(MaxPartySize);
        }

        // Set secrets for joining and spectating
        activity.GetSecrets().SetJoin(TCHAR_TO_ANSI(*JoinSecret));
        activity.GetSecrets().SetSpectate(TCHAR_TO_ANSI(*SpectateSecret));

        // Set whether this activity is an instance (e.g., a match)
        activity.SetInstance(bIsInstance);

        // Update Discord activity
        DiscordCore->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
            if (result == discord::Result::Ok)
            {
                UE_LOG(LogTemp, Log, TEXT("Discord Rich Presence updated successfully with all details."));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to update Discord Rich Presence with all details."));
            }
        });
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Discord Core is not initialized."));
    }
}



// Called when the game starts
void UDiscordRichPresenceComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the Client ID from settings
	FString AppClientID = GetDefault<UDiscordBridgeSettings>()->AppClientID;


	if (AppClientID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord App Client ID is not set in the Discord Bridge settings."));
		return;
	}

	int64 ClientID = FCString::Atoi64(*AppClientID);
	discord::Result result = discord::Core::Create(ClientID, DiscordCreateFlags_Default, &DiscordCore);

	if (result == discord::Result::Ok && DiscordCore)
	{
		UE_LOG(LogTemp, Log, TEXT("Discord Core initialized successfully with Client ID: %s"), *AppClientID);
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


