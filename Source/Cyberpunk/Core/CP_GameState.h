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



	int32 Wave;
	int32 AI_Count;
	float WatingTime;


	FTimerHandle AIWatingTimerHandel; //ai스폰 이후 대기시간 타이머
	FTimerHandle PlayTimerHandle; // 총 플레이 타임 타이머

	void StartWave(); //Wave 시작 함수
	void StartBossWave(); //보스전 시작 함수
	void OnGameOver(); //캐릭터 체력이 0이 됬을 경우 호출
	void KillAll(); //모든 적을 잡았을 때 호출
	void SpawnAI(); //웨이브가 새로 시작할 때 적을 생성하는 함수
	FVector GetRandomSpawnLocation();
};
