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

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:

	UFUNCTION()
	void OnDestroy(AActor* DestroyedActor);

protected:

	UPROPERTY(EditAnywhere, Category = "BossProjectile")
	TObjectPtr<class UParticleSystem> ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "BossProjectile")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "BossProjectile")
	float ProjectileDamage = 100.0f;
};
