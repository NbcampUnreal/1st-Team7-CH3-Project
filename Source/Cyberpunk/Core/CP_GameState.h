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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 WaveCount;

};
