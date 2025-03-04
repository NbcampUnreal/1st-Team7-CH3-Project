#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Character/CP_Enemy.h"
#include "CP_GameMode.generated.h"

UCLASS()
class CYBERPUNK_API ACP_GameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ACP_GameMode();

    virtual void BeginPlay() override;

    UFUNCTION()
    void SpawnItemOnEnemyDeath(const FVector& DeathLocation);  
};
