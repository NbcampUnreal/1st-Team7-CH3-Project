#include "Guns/CP_BossProjectile.h"

#include "Cyberpunk.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

ACP_BossProjectile::ACP_BossProjectile()
{
}

void ACP_BossProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (ExplosionParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorTransform());
    }
    
    Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
