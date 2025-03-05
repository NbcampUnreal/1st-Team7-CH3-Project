#include "Core/CP_GameInstance.h"
#include "Core/CP_PlayerHUD.h"
#include "Core/CP_GameState.h"
#include "Core/CP_DeadMenu.h"

#include "Kismet/GameplayStatics.h"
#include "Cyberpunk.h"

UCP_GameInstance::UCP_GameInstance()
{
	KillCount = 0;
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

	UWorld* World = GetWorld();
	if (!World)
	{
		CP_LOG(Error, TEXT("World is Null"));
		return;
	}
	PlayerHUDInstance = CreateWidget<UCP_PlayerHUD>(World, PlayerHUDClass);

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

void UCP_GameInstance::AddDeadMenuToViewport()
{
	if (DeadMenuClass == nullptr)
	{
		CP_LOG(Error, TEXT("DeadMenuClass == nullptr"));
		return;
	}

	if (DeadMenuInstance)
	{
		DeadMenuInstance->AddToViewport();
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		CP_LOG(Error, TEXT("World is Null"));
		return;
	}

	DeadMenuInstance = CreateWidget<UCP_DeadMenu>(World, DeadMenuClass);

	if (DeadMenuInstance == nullptr)
	{
		CP_LOG(Error, TEXT("DeadMenuInstance == nullptr"));
		return;
	}

	DeadMenuInstance->AddToViewport();
}

void UCP_GameInstance::Decrease_AI()
{
	AI_Counting -= 1;
	if (AI_Counting <= 0)
	{
		ACP_GameState* GameState = Cast<ACP_GameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (GameState)
		{
			GameState->KillAll();
		}
	}
	PlayerHUDInstance->UpdateEnemiesRemaining(AI_Counting);
}

void UCP_GameInstance::Increase_AI()
{
	AI_Counting++;
	if (PlayerHUDInstance)
	{
		PlayerHUDInstance->UpdateEnemiesRemaining(AI_Counting);
	}
}

void UCP_GameInstance::Set_AICount(int32 num)
{
	AI_Counting = num;
	PlayerHUDInstance->UpdateEnemiesRemaining(AI_Counting);
}

int32 UCP_GameInstance::Get_AICount()
{
	return AI_Counting;
}

void UCP_GameInstance::Set_Wave(int32 p_Wave)
{
	Wave = p_Wave;
	PlayerHUDInstance->UpdateWave(Wave);
}

int32 UCP_GameInstance::Get_Wave()
{
	return Wave;
}

void UCP_GameInstance::Increase_KillCount()
{
	KillCount++;
	PlayerHUDInstance->UpdateKillCount(KillCount);
}
