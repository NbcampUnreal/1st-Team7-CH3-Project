#include "Guns/CP_BossProjectileLauncher.h"

#include "CP_Projectile.h"
#include "Cyberpunk.h"

UCP_BossProjectileLauncher::UCP_BossProjectileLauncher()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCP_BossProjectileLauncher::BeginPlay()
{
	Super::BeginPlay();

}

void UCP_BossProjectileLauncher::FireDirectionalProjectile(const FVector& StartPoint, const FVector& TargetPoint, float Speed)
{
    if (DirectionalProjectileClass == nullptr)
    {
        CP_LOG(Warning, TEXT("DirectionalProjectileClass == nullptr"));
        return;
    }

    ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(DirectionalProjectileClass, StartPoint, FRotator::ZeroRotator);
    if (Projectile == nullptr)
    {
        CP_LOG(Warning, TEXT("Projectile == nullptr"));
        return;
    }

    if (Projectile->ProjectileMovement == nullptr)
    {
        CP_LOG(Warning, TEXT("Projectile->ProjectileMovement == nullptr"));
        return;
    }

    Projectile->SetOwner(GetOwner());

    FVector LaunchDirection = TargetPoint - StartPoint;
    LaunchDirection.Normalize();

    FVector Velocity = LaunchDirection * Speed;

    Projectile->ProjectileMovement->Velocity = Velocity;
    Projectile->ProjectileMovement->Activate();
    //Projectile->LaunchProjectile(LaunchDirection);
}

void UCP_BossProjectileLauncher::FireCurveProjectile(const FVector& StartPoint, const FVector& TargetPoint, float Speed)
{
	FVector DirectrionToTarget = TargetPoint - StartPoint;
	FVector CenterPosition = DirectrionToTarget / 2;

	FVector CenterToHeightDirection = DirectrionToTarget + FVector::UpVector;
	CenterToHeightDirection.Normalize();

	float DistanceToTarget = DirectrionToTarget.Length();
	FVector HeightPoint = CenterPosition + CenterToHeightDirection * DistanceToTarget / 2;


}

