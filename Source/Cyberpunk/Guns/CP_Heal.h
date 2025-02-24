#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_Heal.generated.h"

UCLASS()
class CYBERPUNK_API ACP_Heal : public AActor
{
	GENERATED_BODY()

public:
	ACP_Heal();

protected:
	// Heal 아이템용 스태틱 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* HealMesh;
};
