#include "Guns/CP_BossProjectile.h"

#include "Cyberpunk.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

ACP_BossProjectile::ACP_BossProjectile()
{
}

void ACP_BossProjectile::BeginPlay()
{
    Super::BeginPlay();

    OnDestroyed.AddDynamic(this, &ACP_BossProjectile::OnDestroy);
}

void ACP_BossProjectile::OnDestroy(AActor* DestroyedActor)
{
    if (ExplosionParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorTransform());
    }

    if (ExplosionSound)
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
    }
}

void ACP_BossProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        // 데미지 적용
        AActor* OwnerActor = GetOwner();
        AController* OwnerController = nullptr;

        if (OwnerActor)
        {
            APawn* OwnerPawn = Cast<APawn>(OwnerActor);
            if (OwnerPawn)
            {
                OwnerController = OwnerPawn->GetController();
            }
        }

        float TotalDamage = ProjectileDamage;

        if (TotalDamage > 0.0f)
        {
            UGameplayStatics::ApplyDamage(
                OtherActor,
                TotalDamage,
                OwnerController,
                this,
                UDamageType::StaticClass()
            );
        }

        // 프로젝타일 소멸
        Destroy();
    }
}

