#include "Core/CP_GameState.h"
#include "Core/CP_AISpawnPoint.h"
#include "Core/CP_PlayerHUD.h"
#include "Core/CP_GameInstance.h"

#include "Character/CP_PlayerController.h"
#include "Character/CP_NormalEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Cyberpunk.h"


ACP_GameState::ACP_GameState()
{
	Wave = 1;
	MAX_Wave = 3;
	Dealay_Time = 2.0f;
	Number_AI = 0;
	AI_Counting = 0;
}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));

	UE_LOG(LogTemp, Warning, TEXT("StartWave : %d"), Wave);
	GameInstance->AddPlayerHUDToViewport();
	GameInstance->Set_Wave(Wave);
	AI_Spawn_Owner(); //ai spawn 함수

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
	UCP_GameInstance* Instance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));

	if (Number_AI >= 0 && Wave < MAX_Wave)// ai가 모두 죽고 현재 웨이브가 3이하면 다음 웨이브 진행
	{
		Wave++;
		StartWave();
	}
	else if (Number_AI >= 0 && Wave >= MAX_Wave) // 3웨이브를 끝냈다면 보스전 진행
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
	Instance->Set_Wave(Wave);

}

void ACP_GameState::Spawner(int32 Portal_Number)
{
	for (int i = 0; i < Portal_Number; i++)
	{
		AActor* SpawnedAI = GetWorld()->SpawnActor<AActor>(
			EnemyClass,
			SpawnLocation[i],
			FRotator::ZeroRotator,
			SpawnParams
		);
		++AI_Counting;
		
		if (!SpawnedAI)  // AI 스폰이 실패한 경우
		{
			CP_LOG(Warning, TEXT("AI Spawn Failed"));
		}
		else  // AI 스폰이 성공한 경우
		{
			CP_LOG(Warning, TEXT("AI Spawn Success: %s"), *SpawnLocation[i].ToString());
		}

		if (AI_Counting == Number_AI)//AI가 다 스폰되면 생성 중지
		{
			GetWorldTimerManager().ClearTimer(AIWatingTimerHandel);
			AI_Counting = 0;
			break;
		}
	}
}

//AI 스폰 함수
void ACP_GameState::AI_Spawn_Owner()
{
	TArray<AActor*> FoundActors;
	TArray<ACP_AISpawnPoint*> Portal;

	Number_AI = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6

	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
	GameInstance->Set_AICount(Number_AI);
	if (!EnemyClass)  // 블루프린트에서 설정이 안 되었을 경우 방어 코드
	{
		CP_LOG(Warning, TEXT("EnemyClass Didn't Enable"));
		return;
	}

	//월드상에서 ACP_AISpawnPoint 객체를 모두 찾아 FoundActors에 Push
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_AISpawnPoint::StaticClass(), FoundActors);
	int Portal_Number = FoundActors.Num(); //에디터 내 포털 갯수

	//객체가 존재한다면 실행
	if (Portal_Number > 0)
	{
		Portal.SetNum(Portal_Number);
		for (int32 i = 0; i < Portal_Number; i++)
		{
			Portal[i] = Cast<ACP_AISpawnPoint>(FoundActors[i]);
			SpawnLocation.Push(Portal[i]->PortalLocation());
		}

		SpawnParams.Owner = this;

		//스폰위치 충돌이 있을 경우 위치 조정후 스폰
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorldTimerManager().SetTimer(
			AIWatingTimerHandel,
			std::bind(&ACP_GameState::Spawner, this, Portal_Number),
			Dealay_Time,
			true
		);
	}
}