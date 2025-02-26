#pragma once

#include "CoreMinimal.h"
#include "Character/CP_Enemy.h"

#include "CP_CoverEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_CoverEnemy : public ACP_Enemy
{
	GENERATED_BODY()
	
public:

	ACP_CoverEnemy();

protected:

	virtual void BeginPlay() override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AttackNormal() override;

protected:

	virtual void Die() override;

};
