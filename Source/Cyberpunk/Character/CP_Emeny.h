#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"

#include "CP_Emeny.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_Emeny : public ACP_CharacterBase
{
	GENERATED_BODY()
	

public:

	ACP_Emeny();

protected:

	virtual void BeginPlay() override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void Die();
};
