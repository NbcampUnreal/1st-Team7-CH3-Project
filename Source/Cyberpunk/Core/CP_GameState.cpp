
#include "Core/CP_GameState.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_PlayerHUD.h"
#include "Character/CP_NormalEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Core/CP_GameInstance.h"
#include "Cyberpunk.h"
#include "Core/CP_AISpawnPoint.h"

ACP_GameState::ACP_GameState()
{
	Wave = 1;
	WatingTime = 5.0f;
	AI_Count = 0;
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();
	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance == nullptr)
	{
		CP_LOG(Warning, TEXT("GameInstance == nullptr"));
		return;
	}

	GameInstance->AddPlayerHUDToViewport();
	StartWave();

}

void ACP_GameState::StartWave()
{
	UE_LOG(LogTemp, Warning, TEXT("StartWave : %d"), Wave);

	SpawnAI(); //ai spawn 함수

	//임시 타이머. WatingTime초 마다 Kill All함수 호출
	//추후 AI_Count=0 이 되는 시점에서 KillAll 함수 호출 예정
	GetWorldTimerManager().SetTimer(
		AIWatingTimerHandel,
		this,
		&ACP_GameState::KillAll,
		WatingTime,
		false
	);

}

void ACP_GameState::StartBossWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Wave"));

}

void ACP_GameState::OnGameOver()//게임 종료 함수
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

void ACP_GameState::KillAll()//AI가 모두 죽었을 시 호출
{
	UE_LOG(LogTemp, Warning, TEXT("Kill All"));

	if (AI_Count >= 0 && Wave <= 2)// ai가 모두 죽고 현재 웨이브가 2이하면 다음 웨이브 진행
	{
		Wave++;
		UGameInstance* Gameinstance = GetGameInstance();
		UCP_GameInstance* CPGameinstance = Cast<UCP_GameInstance>(Gameinstance);
		CPGameinstance->Wave++;

		StartWave();
	}
	else if (AI_Count >= 0 && Wave > 2) // 3웨이브를 끝냈다면 보스전 진행
	{
		Wave++;
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

//AI 스폰 함수
void ACP_GameState::SpawnAI()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin AI Spawn"));

	AI_Count = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6
	UGameInstance* Gameinstance = GetGameInstance();
	UCP_GameInstance* CPGameinstance = Cast<UCP_GameInstance>(Gameinstance);
	CPGameinstance->AI_Count = AI_Count;

	if (!EnemyClass)  // 블루프린트에서 설정이 안 되었을 경우 방어 코드
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyClass didn't Enable"));
		return;
	}

	//AI 스폰 좌표. 추후 Spawn Zone 클래스 추가 예정
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_AISpawnPoint::StaticClass(), FoundActors);

	// 첫 번째 스폰 포인트를 선택 (필요에 따라 다른 로직으로 선택 가능)
	if (FoundActors.Num() > 0)
	{
		ACP_AISpawnPoint* SpawnPortal = Cast<ACP_AISpawnPoint>(FoundActors[0]);
		if (SpawnPortal)
		{
			FVector SpawnLocation = SpawnPortal->PortalLocation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* SpawnedAI = GetWorld()->SpawnActor<AActor>(
				EnemyClass,
				SpawnLocation,
				FRotator::ZeroRotator,
				SpawnParams
			);

			if (!SpawnedAI)
			{
				CP_LOG(Error, TEXT("AI Spawn Failed"));
			}
			else
			{
				CP_LOG(Warning, TEXT("AI Spawn Sucsess: %s"), *SpawnLocation.ToString());
			}
		}
	}
	

}
