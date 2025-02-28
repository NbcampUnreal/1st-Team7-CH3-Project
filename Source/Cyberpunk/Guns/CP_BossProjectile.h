#pragma once

#include "CoreMinimal.h"
#include "Guns/CP_Projectile.h"

#include "CP_BossProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_BossProjectile : public ACP_Projectile
{
	GENERATED_BODY()
	
public:

	ACP_BossProjectile();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnDestroy(AActor* DestroyedActor);

protected:

	UPROPERTY(EditAnywhere, Category = "BossProjectile")
	TObjectPtr<class UParticleSystem> ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "BossProjectile")
	TObjectPtr<USoundBase> ExplosionSound;
};
