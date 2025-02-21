#include "Core/CP_GameInstance.h"

#include "Cyberpunk.h"
#include "Core/CP_PlayerHUD.h"

UCP_GameInstance::UCP_GameInstance()
{
}

void UCP_GameInstance::Init()
{
	Super::Init();
}

UCP_PlayerHUD* UCP_GameInstance::GetPlayerHUD()
{
	return PlayerHUDInstance;
}

void UCP_GameInstance::AddPlayerHUDToViewport()
{
	if (PlayerHUDClass == nullptr)
	{
		CP_LOG(Error, TEXT("PlayerHUDClass == nullptr"));
		return;
	}

	if (PlayerHUDInstance)
	{
		PlayerHUDInstance->AddToViewport();
		return;
	}

	PlayerHUDInstance = CreateWidget<UCP_PlayerHUD>(GetWorld(), PlayerHUDClass);

	if (PlayerHUDInstance == nullptr)
	{
		CP_LOG(Error, TEXT("PlayerHUDInstance == nullptr"));
		return;
	}

	PlayerHUDInstance->AddToViewport();
}

void UCP_GameInstance::RemovePlayerHUDToViewport()
{
	if (PlayerHUDClass == nullptr)
	{
		CP_LOG(Error, TEXT("PlayerHUDClass == nullptr"));
		return;
	}

	if (PlayerHUDInstance == nullptr)
	{
		CP_LOG(Error, TEXT("PlayerHUDInstance == nullptr"));
		return;
	}

	PlayerHUDInstance->RemoveFromParent();
}
