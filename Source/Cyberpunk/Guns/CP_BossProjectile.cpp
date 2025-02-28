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
