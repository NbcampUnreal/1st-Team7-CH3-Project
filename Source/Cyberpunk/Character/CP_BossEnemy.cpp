#include "Character/CP_BossEnemy.h"

#include "Cyberpunk.h"
#include "Guns/CP_BossProjectileLauncher.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"

ACP_BossEnemy::ACP_BossEnemy()
{
	ProjectileLauncher = CreateDefaultSubobject<UCP_BossProjectileLauncher>(TEXT("ProjectileLauncher"));
}

void ACP_BossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_BossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentHpRatio = (float)CurrentHp / MaxHp;

	if (CurrentHp <= 0.66f && BossPhase == EBossPhase::Phase1)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController == nullptr)
		{
			CP_LOG(Warning, TEXT("AIController == nullptr"));
			return;
		}

		if (Phase2BT == nullptr)
		{
			CP_LOG(Warning, TEXT("Phase2BT == nullptr"));
			return;
		}

		BossPhase = EBossPhase::Phase2;

		AIController->RunBehaviorTree(Phase2BT);
	}
	else if (CurrentHp <= 0.33f && BossPhase == EBossPhase::Phase2)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController == nullptr)
		{
			CP_LOG(Warning, TEXT("AIController == nullptr"));
			return;
		}

		if (Phase2BT == nullptr)
		{
			CP_LOG(Warning, TEXT("Phase2BT == nullptr"));
			return;
		}

		BossPhase = EBossPhase::Phase3;

		AIController->RunBehaviorTree(Phase3BT);
	}
}

float ACP_BossEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_BossEnemy::AttackNormal()
{
	Super::AttackNormal();
}

void ACP_BossEnemy::FireDirectionalProjectile(AActor* Target)
{
	if (Target == nullptr)
	{
		CP_LOG(Warning, TEXT("Target == nullptr"));
		return;
	}

	if (ProjectileLauncher == nullptr)
	{
		CP_LOG(Warning, TEXT("ProjectileLauncher == nullptr"));
		return;
	}

	FVector FireStartPoint = GetMesh()->GetSocketLocation(GunFireSocketName);
	FVector TargetPoint = Target->GetActorLocation();

	ProjectileLauncher->FireDirectionalProjectile(FireStartPoint, TargetPoint, GunProjectileSpeed);
}

void ACP_BossEnemy::FireCurveProjectile(AActor* Target)
{
	if (Target == nullptr)
	{
		CP_LOG(Warning, TEXT("Target == nullptr"));
		return;
	}

	if (ProjectileLauncher == nullptr)
	{
		CP_LOG(Warning, TEXT("ProjectileLauncher == nullptr"));
		return;
	}

	FVector FireStartPoint = GetMesh()->GetSocketLocation(CannonFireSocketName);
	FVector TargetPoint = Target->GetActorLocation();

	ProjectileLauncher->FireCurveProjectile(FireStartPoint, TargetPoint, CannonProjectileSpeed);
}

void ACP_BossEnemy::PlayGunFireAnim()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		CP_LOG(Warning, TEXT("AnimInstance == nullptr"));
		return;
	}

	AnimInstance->Montage_Play(GunFireAnim);
}

void ACP_BossEnemy::PlayCannonFireAnim()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		CP_LOG(Warning, TEXT("AnimInstance == nullptr"));
		return;
	}


	if (BossPhase == EBossPhase::Phase3)
	{
		AnimInstance->Montage_Play(CannonFireWithAnnyingAnim);
	}
	else
	{
		AnimInstance->Montage_Play(CannonFireAnim);
	}
}

bool ACP_BossEnemy::IsFiring() const
{
	return bIsFiring;
}

void ACP_BossEnemy::SetFiring(bool bShouldFire)
{
	bIsFiring = bShouldFire;
}

bool ACP_BossEnemy::IsAming() const
{
	return bIsAming;
}

void ACP_BossEnemy::SetAming(bool bIsAmingNow)
{
	bIsAming = bIsAmingNow;
}

void ACP_BossEnemy::Die()
{
	Super::Die();
}
