#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Ammo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Ammo : public AActor
{
	GENERATED_BODY()

public:
	ACP_Ammo();

	// 아이템 식별용 이름 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AmmoMesh;
};
