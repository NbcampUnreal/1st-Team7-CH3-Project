#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Gear.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Gear : public AActor
{
	GENERATED_BODY()

public:
	ACP_Gear();

protected:
	// Gear 아이템용 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GearMesh;
};
