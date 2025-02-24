#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CP_GameState.generated.h"


UCLASS()
class CYBERPUNK_API ACP_GameState : public AGameState
{
	GENERATED_BODY()
public:

	ACP_GameState();
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 MAX_Wave; //Wave 수
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	float Dealay_Time; //스폰사이 딜레이 타임
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<AActor> EnemyClass; //스폰시킬 ai 타입


	int32 Wave;
	int32 Number_AI; //신경안쓰셔도 됩니다
	int32 AI_Counting; //스폰시킬 AI수
	FTimerHandle AIWatingTimerHandel; //ai스폰 이후 대기시간 타이머
	FTimerHandle PlayTimerHandle; // 총 플레이 타임 타이머
	FVector SpawnLocation;
	FActorSpawnParameters SpawnParams;

	void StartWave(); //Wave 시작 함수
	void StartBossWave(); //보스전 시작 함수
	void OnGameOver(); //캐릭터 체력이 0이 됬을 경우 호출
	void KillAll(); //모든 적을 잡았을 때 호출
	void AI_Spawn_Owner(); //웨이브가 새로 시작할 때 적을 생성하는 함수
	void Spawner();
};
