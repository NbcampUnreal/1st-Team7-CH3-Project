#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"

#include "CP_PlayerTurret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_PlayerTurret : public ACP_CharacterBase
{
	GENERATED_BODY()

public:

	ACP_PlayerTurret();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void Die() override;
	virtual void BreakBones(FHitResult HitInfo);

public:

	void Attack();

	// Yaw 회전
	void RotateTurret(float DeltaRotation);
	// 타겟 바라보기
	void AimTarget(const class ACP_Enemy* Target);

public:

	float GetRotateSpeed();
	float GetAttackRange();

protected:

	void RotatePitch(float DeltaRotation);
	void RotateBody(float DeltaRotation);
	void RotateLowerBody(float DeltaRotation);

protected:

	UPROPERTY(EditAnywhere, Category = "Turret")
	float RotateSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "Turret")
	TSet<FName> UpperBodyBones;

	UPROPERTY(EditAnywhere, Category = "Turret")
	TSet<FName> LowerBodyBones;

	UPROPERTY(VisibleAnywhere, Category = "Turret")
	TObjectPtr<USkeletalMeshComponent> LowerBodyMeshComp;

	UPROPERTY(EditAnywhere, Category = "Turret")
	float AttackRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Turret")
	float AttackDamage = 1;

	UPROPERTY(EditAnywhere, Category = "Turret")
	TSet<FName> BreakingBoneExceptionList;

protected:

	float OriginalMeshRelativeYaw = 0;
};
