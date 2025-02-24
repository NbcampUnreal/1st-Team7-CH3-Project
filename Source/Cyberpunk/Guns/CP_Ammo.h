#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Item.h"
#include "CP_Ammo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Ammo : public AActor, public ICP_Item
{
    GENERATED_BODY()

public:
    ACP_Ammo();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* AmmoMesh;
};
