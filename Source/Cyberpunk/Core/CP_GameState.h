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
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<AActor> HiddenEnemyClass; //스폰시킬 ai 타입
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	int32 Portal_Nums; //스폰시킬 포탈 갯수

	int32 Wave; //웨이브 단계
	int32 Number_AI; //생성할 AI 수
	int32 AI_Counting; //생성된 AI 수
	FTimerHandle AIWatingTimerHandel; //ai스폰 이후 대기시간 타이머
	FTimerHandle PlayTimerHandle; // 총 플레이 타임 타이머
	FActorSpawnParameters SpawnParams;

	void StartWave(); //Wave 시작 함수
	void SpawnPortal(); //랜덤위치 포털 생성함수
	void OnGameOver(); //캐릭터 체력이 0이 됬을 때, 보스전이 끝났을 때
	void KillAll(); //모든 적을 잡았을 때 호출
	void AI_Spawn_Owner(); //웨이브가 새로 시작할 때 적을 생성하는 함수
	void Spawner(TArray<FVector> SpawnLocation);
	void Boss_Spawner(TArray<FVector> SpawnLocation); //보스전 시작 함수
};
