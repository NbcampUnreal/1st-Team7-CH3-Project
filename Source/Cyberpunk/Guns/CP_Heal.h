#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Item.h"
#include "CP_Heal.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Heal : public AActor, public ICP_Item
{
    GENERATED_BODY()

public:
    ACP_Heal();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* HealMesh;
};
