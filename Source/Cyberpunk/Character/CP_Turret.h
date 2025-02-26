#pragma once

#include "CoreMinimal.h"
#include "Character/CP_Enemy.h"

#include "CP_Turret.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API ACP_Turret : public ACP_Enemy
{
	GENERATED_BODY()

public:

	ACP_Turret();

public:

	virtual void BeginPlay() override;
	
	virtual void AttackNormal() override;

	// Yaw 회전
	void RotateTurret(float DeltaRotation);
	// 플레이어 바라보기
	void AimPlayer(const class ACP_Player* Player);

public:

	float GetRotateSpeed();

	bool GetShouldRotate();
	void SetShouldRotate(bool bNewShouldRotate);

protected:

	void RotatePitch(float DeltaRotation);
	void RotateBody(float DeltaRotation);
	void RotateLowerBody(float DeltaRotation);

protected:

	UPROPERTY(EditAnywhere, Category = "Turret")
	float RotateSpeed;

	UPROPERTY(EditAnywhere, Category = "Turret")
	TSet<FName> UpperBodyBones;

	UPROPERTY(EditAnywhere, Category = "Turret")
	TSet<FName> LowerBodyBones;

	UPROPERTY(VisibleAnywhere, Category = "Turret")
	TObjectPtr<USkeletalMeshComponent> LowerBodyMeshComp;

	float OriginalMeshRelativeYaw = 0;
	bool bShouldRotate = false;
};

