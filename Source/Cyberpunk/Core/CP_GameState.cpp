
#include "Core/CP_GameState.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_PlayerHUD.h"
#include "Character/CP_NormalEnemy.h"

ACP_GameState::ACP_GameState()
{
	Wave = 0;
	WatingTime = 3.0f;
	AI_Count = 0;
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	SpawnAI();
	//AI스폰이후 WatingTime초가 지나면 이동시작 이동함수 미구현으로 주석처리.
	/*GetWorldTimerManager().SetTimer(
		AIWatingTimerHandel,
		this,
		&CP_EnemyAI::StartMove,
		WatingTime,
		false
	);*/

}

void ACP_GameState::StartBossWave()
{

}

void ACP_GameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ACP_PlayerController* CP_PlayerController = Cast<ACP_PlayerController>(PlayerController))
		{
			CP_PlayerController->SetPause(true);
			// CP_PlayerHUD->ShowMainMenu(); //미구현
		}
	}
}

void ACP_GameState::KillAll()
{
	if (AI_Count >= 0 && Wave <= 3)// ai가 모두 죽고 현재 웨이브가 2이하면 다음 웨이브 진행
	{
		StartWave();
	}
	else if (AI_Count >= 0 && Wave > 2) // 3웨이브를 끝냈다면 보스전 진행
	{
		StartBossWave();
	}
	else //보스전 종료
	{
		if (Wave > 3)
		{
			OnGameOver();
		}
	}
}

void ACP_GameState::SpawnAI()
{

	AI_Count = ((Wave * 3) + 1) / 2; //2, 3, 5, 6

	for (int32 i = 0; i < AI_Count; ++i)
	{
		FVector SpawnLocation = GetRandomSpawnLocation(); // 적이 스폰할 위치
		

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ACP_NormalEnemy* SpawnedAI = GetWorld()->SpawnActor<ACP_NormalEnemy>(
			ACP_NormalEnemy::StaticClass(), 
			SpawnLocation, 
			FRotator::ZeroRotator,
			SpawnParams);


	}
}

FVector ACP_GameState::GetRandomSpawnLocation()
{
}