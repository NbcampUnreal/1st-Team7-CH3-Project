#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"

#include "CP_Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeadDelegate, const FVector&, DeadPosition);

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_Enemy : public ACP_CharacterBase
{
	GENERATED_BODY()
	
public:

	ACP_Enemy();

protected:

	virtual void BeginPlay() override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AttackNormal();
protected:

	virtual void Die() override;
	
	virtual void BreakBones(FHitResult HitInfo);

	// getter, setter
public:

	float GetAttackRange();

public:

	UPROPERTY(BlueprintAssignable)
	FOnEnemyDeadDelegate OnEnemyDeadDelegate;

protected:

	UPROPERTY(EditAnywhere, Category = "EnemySettings")
	float AttackDamage = 1;

	UPROPERTY(EditAnywhere, Category = "EnemySettings")
	TSet<FName> BreakingBoneExceptionList;

	UPROPERTY(EditAnywhere, Category = "EnemySettings")
	float AttackRange = 500.0f;

private:

	static int32 AvoidanceUID;

};
