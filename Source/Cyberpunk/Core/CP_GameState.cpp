
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

	SpawnAI(); //ai spawn �Լ�

	//�ӽ� Ÿ�̸�. WatingTime�� ���� Kill All�Լ� ȣ��
	//���� AI_Count=0 �� �Ǵ� �������� KillAll �Լ� ȣ�� ����
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

void ACP_GameState::OnGameOver()//���� ���� �Լ�
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ACP_PlayerController* CP_PlayerController = Cast<ACP_PlayerController>(PlayerController))
		{
			CP_PlayerController->SetPause(true);
			// CP_PlayerHUD->ShowMainMenu(); //�̱���
		}
	}
}

void ACP_GameState::KillAll()//AI�� ��� �׾��� �� ȣ��
{
	UE_LOG(LogTemp, Warning, TEXT("Kill All"));

	if (AI_Count >= 0 && Wave <= 2)// ai�� ��� �װ� ���� ���̺갡 2���ϸ� ���� ���̺� ����
	{
		Wave++;
		UGameInstance* Gameinstance = GetGameInstance();
		UCP_GameInstance* CPGameinstance = Cast<UCP_GameInstance>(Gameinstance);
		CPGameinstance->Wave++;

		StartWave();
	}
	else if (AI_Count >= 0 && Wave > 2) // 3���̺긦 ���´ٸ� ������ ����
	{
		Wave++;
		StartBossWave();
	}
	else //������ ����
	{
		if (Wave > 3)
		{
			OnGameOver();
		}
	}
}

//AI ���� �Լ�
void ACP_GameState::SpawnAI()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin AI Spawn"));

	AI_Count = ((Wave * 3) + 1) / 2; // 2, 3, 5, 6
	UGameInstance* Gameinstance = GetGameInstance();
	UCP_GameInstance* CPGameinstance = Cast<UCP_GameInstance>(Gameinstance);
	CPGameinstance->AI_Count = AI_Count;

	if (!EnemyClass)  // �������Ʈ���� ������ �� �Ǿ��� ��� ��� �ڵ�
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyClass didn't Enable"));
		return;
	}

	//AI ���� ��ǥ. ���� Spawn Zone Ŭ���� �߰� ����
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACP_AISpawnPoint::StaticClass(), FoundActors);

	// ù ��° ���� ����Ʈ�� ���� (�ʿ信 ���� �ٸ� �������� ���� ����)
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
