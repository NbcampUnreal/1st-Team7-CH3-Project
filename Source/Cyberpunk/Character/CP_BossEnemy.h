#pragma once

#include "CoreMinimal.h"
#include "Character/CP_Enemy.h"

#include "CP_BossEnemy.generated.h"

UENUM()
enum class EBossPhase : uint8
{
	Phase1,
	Phase2,
	Phase3
};

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_BossEnemy : public ACP_Enemy
{
	GENERATED_BODY()
	
public:

	ACP_BossEnemy();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AttackNormal(AActor* Target) override;

public:

	void FireDirectionalProjectile(AActor* Target);
	void FireCurveProjectile(AActor* Target);

	void PlayGunFireAnim();
	void PlayCannonFireAnim();
	void PlayHitAnim();
	
	// getter, setter
public:

	bool IsFiring() const;
	void SetFiring(bool bShouldFire);

	UFUNCTION(BlueprintCallable)
	bool IsAming() const;
	void SetAming(bool bIsAmingNow);

	UFUNCTION(BlueprintCallable)
	bool IsCannonMode() const;
	void SetCannonMode(bool bShouldSetCannon);

	UFUNCTION(BlueprintCallable)
	bool IsReturnedToIdle() const;
	void SetReturnedToIdle(bool bIsReturned);

	bool IsHit() const;
	void SetHit(bool bNewIsHit);

protected:

	virtual void Die() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "BossEnemy")
	TObjectPtr<class UCP_BossProjectileLauncher> ProjectileLauncher;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<UAnimMontage> GunFireAnim;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<UAnimMontage> CannonFireAnim;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<UAnimMontage> CannonFireWithAnnyingAnim;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<UAnimMontage> HitAnim;

	UPROPERTY(VisibleAnywhere, Category = "BossEnemy")
	bool bIsFiring = false;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	FName GunFireSocketName;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	FName CannonFireSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossEnemy")
	float GunProjectileSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossEnemy")
	float CannonProjectileSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	float GunFireDirectionErrorRange = 100;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	float CannonFireDestinationErrorRange = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossEnemy")
	EBossPhase BossPhase = EBossPhase::Phase1;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<class UBehaviorTree> Phase1BT;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<class UBehaviorTree> Phase2BT;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<class UBehaviorTree> Phase3BT;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<USoundBase> DieSound;

	UPROPERTY(EditAnywhere, Category = "BossEnemy")
	TObjectPtr<UParticleSystem> DieParticle;

protected:

	bool bIsAming = false;
	bool bIsCannonMode = false;
	bool bIsReturnedToIdle = true;
	bool bIsHit = false;
};
