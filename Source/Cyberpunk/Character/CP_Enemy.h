#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"

#include "CP_Enemy.generated.h"

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

protected:

	UPROPERTY(EditAnywhere, Category = "EnemySettings")
	float AttackDamage = 1;

	UPROPERTY(EditAnywhere, Category = "EnemySettings")
	TSet<FName> BreakingBoneExceptionList;

};
