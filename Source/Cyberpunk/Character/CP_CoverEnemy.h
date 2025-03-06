#pragma once

#include "CoreMinimal.h"
#include "Character/CP_Enemy.h"
#include "Guns/CP_GunS.h"
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
	virtual void AttackNormal(AActor* Target) override;

protected:

	virtual void BreakBones() override;
	virtual void Die() override;


	UPROPERTY()
	ACP_Guns* Gun;  // 무기 인스턴스

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ACP_Guns> GunClass;  // 무기 클래스 지정

};
