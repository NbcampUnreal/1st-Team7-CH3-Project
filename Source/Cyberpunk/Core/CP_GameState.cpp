#include "Core/CP_GameState.h"
#include "Core/CP_AISpawnPoint.h"
#include "Core/CP_PlayerHUD.h"
#include "Core/CP_GameInstance.h"
#include "Core/CP_PotalSpawnPoint.h"

#include "Character/CP_PlayerController.h"
#include "Character/CP_NormalEnemy.h"
#include "Character/CP_CoverEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Cyberpunk.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"

ACP_GameState::ACP_GameState()
{
	Wave = 1;
	MAX_Wave = 4;
	Dealay_Time = 2.0f;
	Number_AI = 0;
	AI_Counting = 0;
	Portal_Nums = 2;

	SpawnParams.Owner = this;
	//스폰위치 충돌이 있을 경우 위치 조정후 스폰
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

}

void ACP_GameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

}

void ACP_GameState::StartWave()
{
	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));

	// 존재하는 포털 모두 제거

	UWorld* World = GetWorld();
	for (TActorIterator<ACP_AISpawnPoint> It(World); It; ++It)
	{
		ACP_AISpawnPoint* Actor = *It;
		if (Actor)
		{
			Actor->Destroy();
		}
	}
	SpawnPortal();


	UE_LOG(LogTemp, Warning, TEXT("StartWave : %d"), Wave);
	GameInstance->AddPlayerHUDToViewport(); //이게 객체를 생성시켜서 앞에 있어야됨
	GameInstance->Set_Wave(Wave);
	AI_Spawn_Owner(); //ai spawn 함수

}

void ACP_GameState::SpawnPortal() //월드에 있는 Spawn Portal Point를 모두 찾아 저장후 랜덤좌표에 portal 생성
{
	TArray<AActor*> FoundActors;
	TArray<ACP_PotalSpawnPoint*> Portal;
	TArray<FVector>PortalSpawnLocation;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_PotalSpawnPoint::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0)
	{
		return;  // 아무 것도 없으면 그냥 리턴
	}

	Portal.SetNum(FoundActors.Num());
	if (Portal_Nums > Portal.Num())
	{
		CP_LOG(Warning, TEXT("Over Portal Spawn. add more BP_PortalSpawnPoint"));
	}

	for (int32 i = 0; i < FoundActors.Num(); i++)
	{
		ACP_PotalSpawnPoint* SpawnPoint = Cast<ACP_PotalSpawnPoint>(FoundActors[i]);
		if (!SpawnPoint) continue; // 캐스팅 실패하면 건너뛰기
		Portal[i] = SpawnPoint;
		PortalSpawnLocation.Push(SpawnPoint->PortalLocation());
	}

	AActor* SpawnPortal;
	UClass* SpawnPortalClass = LoadObject<UClass>(nullptr, TEXT("/Game/_Game/CoreBP/BP_AISpawnPortal.BP_AISpawnPortal_C"));
	TArray<int32> Check_SamePoint;

	for (int32 i = 0; i < Portal_Nums; i++)
	{
		int32 RandNum = FMath::RandRange(0, PortalSpawnLocation.Num() - 1);
		if (Check_SamePoint.Num() > 0)
		{

			for (int j = 0; j < Check_SamePoint.Num(); j++)
			{
				if (RandNum == Check_SamePoint[j])
				{
					while (RandNum == Check_SamePoint[j])
					{
						RandNum = FMath::RandRange(0, PortalSpawnLocation.Num() - 1);

					}
				}
			}

			SpawnPortal = GetWorld()->SpawnActor<AActor>(
				SpawnPortalClass,
				PortalSpawnLocation[RandNum],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		else
		{
			SpawnPortal = GetWorld()->SpawnActor<AActor>(
				SpawnPortalClass,
				PortalSpawnLocation[RandNum],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		Check_SamePoint.Push(RandNum);

	}
}


void ACP_GameState::OnGameOver()//게임 종료 함수
{
	CP_LOG(Warning, TEXT("GameOver"));

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

	if (Wave < MAX_Wave)
	{
		Wave++;
		StartWave();
	}
	else //보스전 종료
	{
		OnGameOver();

	}
	Instance->Set_Wave(Wave);

}

//AI 스폰 함수
void ACP_GameState::AI_Spawn_Owner()
{
	TArray<AActor*> FoundActors;
	TArray<ACP_AISpawnPoint*> Portal;
	TArray<FVector>SpawnLocation;
	if (Wave < MAX_Wave) Number_AI = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6
	else Number_AI = 1;

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

	if (Portal_Number > 0)
	{
		Portal.SetNum(Portal_Number);
		for (int32 i = 0; i < Portal_Number; i++)
		{
			Portal[i] = Cast<ACP_AISpawnPoint>(FoundActors[i]);
			SpawnLocation.Push(Portal[i]->PortalLocation());
		}

		if (Wave < MAX_Wave)
		{
			GetWorldTimerManager().SetTimer(
				AIWatingTimerHandel,
				std::bind(&ACP_GameState::Spawner, this, SpawnLocation),
				Dealay_Time,
				true
			);
		}
		else
		{
			Boss_Spawner(SpawnLocation);
		}
	}
}

void ACP_GameState::Spawner(TArray<FVector> SpawnLocation)
{
	for (int i = 0; i < SpawnLocation.Num(); i++)
	{
		AActor* SpawnedAI;
		if (i % 3 == 0)
		{
			SpawnedAI = GetWorld()->SpawnActor<AActor>(
				EnemyClass,
				SpawnLocation[i],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		else
		{
			SpawnedAI = GetWorld()->SpawnActor<AActor>(
				HiddenEnemyClass,
				SpawnLocation[i],
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		++AI_Counting;
		if (!SpawnedAI)
		{
			CP_LOG(Warning, TEXT("AI Spawn Failed"));
		}
		else
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

void ACP_GameState::Boss_Spawner(TArray<FVector> SpawnLocation)
{
	UClass* BossClass = LoadObject<UClass>(nullptr, TEXT("/Game/_Game/Enemy/BP_BossEnemy.BP_BossEnemy_C"));

	if (BossClass)
	{
		AActor* SpawnedAI = GetWorld()->SpawnActor<AActor>(BossClass, SpawnLocation[0], FRotator::ZeroRotator,
			SpawnParams);
		CP_LOG(Warning, TEXT("Boss Wave"));
	}
	++AI_Counting;
}

