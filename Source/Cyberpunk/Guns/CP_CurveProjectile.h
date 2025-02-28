#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CP_CurveProjectile.generated.h"

UCLASS()
class CYBERPUNK_API ACP_CurveProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ACP_CurveProjectile();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:

	void InitProjectile(const FVector& NewTargetPoint, float NewSpeed, AActor* NewIgnoredActor);
	void InitProjectile(const FVector& NewTargetPoint, AActor* NewIgnoredActor);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveProjectile")
	TObjectPtr<class USphereComponent> SphereCollisionComponent;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	TObjectPtr<UParticleSystem> HitParticle;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	float ProjectileDamage = 1.0f;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	float ExplosionRadius = 100.0f;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	TSubclassOf<AActor> DecalActorClass;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "CurveProjectile")
	float MaxHeight = 3800.0f;

private:

	// 베지어 2차 곡선
	FVector QuadraticBezierInterp(const FVector& InStartPoint, const FVector& InControlPoint, const FVector& InEndPoint, float Progress);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	FVector StartPoint;
	FVector ControlPoint;
	FVector TargetPoint;
	
	float CurrentProgress = 0.0f;

	UPROPERTY()
	TObjectPtr<AActor> IgnoredActor;
	TObjectPtr<AActor> CurrentDecal;
};
