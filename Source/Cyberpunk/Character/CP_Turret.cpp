#include "Character/CP_Turret.h"

#include "Cyberpunk.h"
#include "Character/CP_Player.h"

#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

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
}

void ACP_Turret::AttackNormal()
{
	Super::AttackNormal();


	FHitResult HitResult;
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + GetActorForwardVector() * AttackRange;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);
	if (bIsHit)
	{
		ACP_CharacterBase* DamagedCharacter = Cast<ACP_CharacterBase>(HitResult.GetActor());
		if (DamagedCharacter == nullptr)
		{
			CP_LOG(Warning, TEXT("DamagedCharacter == nullptr"));
			return;
		}
		
		UGameplayStatics::ApplyDamage(DamagedCharacter, 1, GetController(), this, nullptr);
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 3);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
	}
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

	//FVector Direction = TargetLocation - StartLocation;
	//Direction.Z = 0.0f; // ZÃà °íÁ¤

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); ;// Direction.Rotation();
	FRotator CurrentRotation = GetActorRotation();
	
	float DeltaRotation = NewRotation.Yaw - CurrentRotation.Yaw;
	
	if (FMath::Abs(DeltaRotation) > 1)
	{
		DeltaRotation = (DeltaRotation > 0) ? 1 : -1;
	}
	
	RotateTurret(DeltaRotation * GetWorld()->GetDeltaSeconds() * RotateSpeed);
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

float ACP_Turret::GetAttackRange()
{
	return AttackRange;
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
