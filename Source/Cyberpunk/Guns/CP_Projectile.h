#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"  
#include "NiagaraFunctionLibrary.h"  
#include "CP_Projectile.generated.h"


class ACP_GUNS;
UCLASS()
class CYBERPUNK_API ACP_Projectile : public AActor
{
    GENERATED_BODY()

public:
    ACP_Projectile();

protected:
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UNiagaraComponent* NiagaraEffect;

    // Projectile Movement
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // 발사 함수
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void LaunchProjectile(const FVector& LaunchDirection);

    bool bIsNPCProjectile = false;

protected:
    // 충돌 발생 시 호출될 함수
    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);
};
