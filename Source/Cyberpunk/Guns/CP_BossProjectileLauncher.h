#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CP_BossProjectileLauncher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERPUNK_API UCP_BossProjectileLauncher : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCP_BossProjectileLauncher();

protected:

	virtual void BeginPlay() override;

public:

	void FireDirectionalProjectile(const FVector& StartPoint, const FVector& TargetPoint, float Speed);
	void FireCurveProjectile(const FVector& StartPoint, const FVector& TargetPoint, float Speed);

protected:

	UPROPERTY(EditAnywhere, Category = "BossProjectileLauncher")
	TSubclassOf<class ACP_Projectile> DirectionalProjectileClass;

	/*UPROPERTY(EditAnywhere, Category = "BossProjectileLauncher")
	TSubclassOf<class ACP_Projectile> CurveProjectileClass;*/
};
