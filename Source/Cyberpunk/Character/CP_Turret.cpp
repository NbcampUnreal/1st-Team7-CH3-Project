#include "Character/CP_Turret.h"

#include "Cyberpunk.h"
#include "Character/CP_Player.h"

#include "Components/PoseableMeshComponent.h"

ACP_Turret::ACP_Turret()
{
	LowerBodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMeshComp"));
	LowerBodyMeshComp->SetupAttachment(RootComponent);

}

void ACP_Turret::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* UpperBodyMeshComp = GetMesh();
	if (UpperBodyMeshComp == nullptr)
	{
		CP_LOG(Warning, TEXT("UpperBodyMeshComp == nullptr"));
		return;
	}

	for (auto& BoneName : UpperBodyBones)
	{
		LowerBodyMeshComp->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	}

	for (auto& BoneName : LowerBodyBones)
	{
		UpperBodyMeshComp->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	}

	OriginalMeshRelativeYaw = UpperBodyMeshComp->GetRelativeRotation().Yaw;

	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	//	{
	//		RotateTurret(RotateSpeed);
	//	}, 0.02, true);
}

void ACP_Turret::AttackNormal()
{
	Super::AttackNormal();


}

void ACP_Turret::RotateTurret(float DeltaRotation)
{
	RotateBody(DeltaRotation);
	RotateLowerBody(-DeltaRotation);
}

void ACP_Turret::AimPlayer(const ACP_Player* Player)
{
	FVector StartLocation = GetActorLocation();
	FVector TargetLocation = Player->GetActorLocation();

	FVector Direction = TargetLocation - StartLocation;
	Direction.Z = 0.0f; // ZÃà °íÁ¤

	FRotator NewRotation = Direction.Rotation();
	FRotator CurrentRotation = GetActorRotation();

	RotateTurret(NewRotation.Yaw - CurrentRotation.Yaw);
}

float ACP_Turret::GetRotateSpeed()
{
	return RotateSpeed;
}

bool ACP_Turret::GetShouldRotate()
{
	return bShouldRotate;
}

void ACP_Turret::SetShouldRotate(bool bNewShouldRotate)
{
	bShouldRotate = bNewShouldRotate;
}

void ACP_Turret::RotatePitch(float DeltaRotation)
{
}

void ACP_Turret::RotateBody(float DeltaRotation)
{
	AddActorLocalRotation(FRotator(0, DeltaRotation, 0));
}

void ACP_Turret::RotateLowerBody(float DeltaRotation)
{
	if (LowerBodyMeshComp == nullptr)
	{
		CP_LOG(Warning, TEXT("LowerBodyMeshComp == nullptr"));
		return;
	}

	LowerBodyMeshComp->AddLocalRotation(FRotator(0, DeltaRotation, 0));
}
