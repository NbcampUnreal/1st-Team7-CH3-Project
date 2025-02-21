#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"  // Niagara 시스템을 사용하기 위한 헤더 추가
#include "NiagaraFunctionLibrary.h"  // Niagara 시스템 함수 라이브러리 추가
#include "CP_Projectile.generated.h"

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

private:
    // 충돌 발생 시 호출될 함수
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);
};
