#include "Character/CP_PlayerTurret.h"

#include "Cyberpunk.h"
#include "Character/CP_Enemy.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"

ACP_PlayerTurret::ACP_PlayerTurret()
{
	LowerBodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMeshComp"));
	LowerBodyMeshComp->SetupAttachment(RootComponent);
	TeamType = ETeamType::PlayerTeam;

	PrimaryActorTick.bCanEverTick = true;
}

void ACP_PlayerTurret::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* UpperBodyMeshComp = GetMesh();
	if (UpperBodyMeshComp == nullptr)
	{
		CP_LOG(Warning, TEXT("UpperBodyMeshComp == nullptr"));
		return;
	}

	OriginalMeshRelativeYaw = UpperBodyMeshComp->GetRelativeRotation().Yaw;

	TArray<UMaterialInterface*> OriginalMaterials = LowerBodyMeshComp->GetMaterials();

	for (int i = 0; i < OriginalMaterials.Num(); ++i)
	{
		UMaterialInterface* OriginalMaterial = OriginalMaterials[i];
		if (OriginalMaterial == nullptr)
		{
			CP_LOG(Warning, TEXT("OriginalMaterial == nullptr, Index : %d"), i);
			continue;
		}
		CP_LOG(Warning, TEXT("Material : %s"), *OriginalMaterial->GetName());
		UMaterialInstanceDynamic* Dynamic = UMaterialInstanceDynamic::Create(OriginalMaterial, LowerBodyMeshComp);
		CurrentDissolveMaterialInstanceArray.Emplace(MoveTemp(Dynamic));
		LowerBodyMeshComp->SetMaterial(i, CurrentDissolveMaterialInstanceArray.Last());
	}
}

void ACP_PlayerTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACP_PlayerTurret::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	CP_LOG(Log, TEXT("Damaged Character : %s"), *GetName());

	int32 HpAfterDamage = CurrentHp - NewDamage;

	CurrentHp = FMath::Clamp(HpAfterDamage, 0, HpAfterDamage);

	if (CurrentHp == 0)
	{
		Die();

		if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
		{
			const FPointDamageEvent& PointDamageEvent = (const FPointDamageEvent&)DamageEvent;
			BreakBones(PointDamageEvent.HitInfo);
		}
	}
	
	return NewDamage;
}

void ACP_PlayerTurret::Die()
{
	Super::Die();

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp == nullptr)
	{
		CP_LOG(Warning, TEXT("CapsuleComp == nullptr, Name : "), *GetName());
		return;
	}

	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DeadTimerHandle;

	GetWorldTimerManager().SetTimer(DeadTimerHandle, [&]()
		{
			if (::IsValid(this) && ::IsValid(GetWorld()))
			{
				Destroy();
			}

		}, 3.0f, false);
}

void ACP_PlayerTurret::BreakBones(FHitResult HitInfo)
{
	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh == nullptr)
	{
		CP_LOG(Error, TEXT("MyMesh == nullptr, Name : "), *GetName());
		return;
	}

	MyMesh->SetAnimInstanceClass(nullptr);
	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetCollisionProfileName(TEXT("Ragdoll"));

	FVector Impulse = FVector::ZeroVector;
	Impulse *= 10.0f;

	FName& BoneName = HitInfo.BoneName;

	FVector HitLocation = MyMesh->GetBoneLocation(BoneName);

	MyMesh->bUpdateJointsFromAnimation = false;

	MyMesh->SetAllBodiesBelowPhysicsBlendWeight(BoneName, 1.0f);
	MyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MyMesh->SetAllBodiesBelowSimulatePhysics(BoneName, true, true);

	if (BreakingBoneExceptionList.Contains(BoneName) == false)
	{
		MyMesh->BreakConstraint(Impulse, HitLocation, BoneName);
	}

	int BoneCount = MyMesh->GetNumBones();

	for (int i = 0; i < BoneCount; ++i)
	{
		BoneName = MyMesh->GetBoneName(i);

		if (BreakingBoneExceptionList.Contains(BoneName))
		{
			continue;
		}

		MyMesh->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector, BoneName);
	}

	//Mesh->AddRadialForce(HitCharacter->GetActorLocation(), 100.0f, 1000, ERadialImpulseFalloff::RIF_Linear, true);

	//Mesh->WakeAllRigidBodies();
	//Mesh->SetSimulatePhysics(true);
	//Mesh->RecreatePhysicsState();
	//Mesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	CP_LOG(Log, TEXT("Hit, BoneName : %s"), *HitInfo.BoneName.ToString());
	//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 3.0f);
}

void ACP_PlayerTurret::Attack(AActor* Target)
{
	FHitResult HitResult;
	FVector StartPoint = GetActorLocation();
	FVector EndPoint = StartPoint + GetActorForwardVector() * AttackRange;
	EndPoint.Z = Target->GetActorLocation().Z;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, StartPoint, EndPoint, ObjectQueryParams, QueryParams);
	if (bIsHit)
	{
		ACP_Enemy* DamagedCharacter = Cast<ACP_Enemy>(HitResult.GetActor());
		if (DamagedCharacter == nullptr)
		{
			CP_LOG(Warning, TEXT("DamagedCharacter == nullptr"));
			return;
		}

		FPointDamageEvent DamageEvent;
		DamagedCharacter->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

		//UGameplayStatics::ApplyDamage(DamagedCharacter, AttackDamage, GetController(), this, nullptr);
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 3);
		CP_LOG(Warning, TEXT("Turret Damaging Target"));
	}
	else
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1);
	}

	OnPlayerTurrentAttack.Broadcast(EndPoint);
}

void ACP_PlayerTurret::RotateTurret(float DeltaRotation)
{
	RotateBody(DeltaRotation);
	RotateLowerBody(-DeltaRotation);
}

void ACP_PlayerTurret::AimTarget(const ACP_Enemy* Target)
{
	FVector StartLocation = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Direction.Rotation();
	FRotator CurrentRotation = GetActorRotation();
	
	float DeltaRotation = FMath::UnwindDegrees(NewRotation.Yaw - CurrentRotation.Yaw);
	float Sign = (DeltaRotation > 0) ? 1 : -1;
	float DeltaRotationPerTime = GetWorld()->GetDeltaSeconds() * RotateSpeed * Sign;

	if (FMath::Abs(DeltaRotation) < DeltaRotationPerTime)
	{
		DeltaRotationPerTime = DeltaRotation;
	}

	RotateTurret(DeltaRotationPerTime);
}

float ACP_PlayerTurret::GetRotateSpeed()
{
	return RotateSpeed;
}

float ACP_PlayerTurret::GetAttackRange()
{
	return AttackRange;
}

void ACP_PlayerTurret::RotatePitch(float DeltaRotation)
{
}

void ACP_PlayerTurret::RotateBody(float DeltaRotation)
{
	AddActorLocalRotation(FRotator(0, DeltaRotation, 0));
}

void ACP_PlayerTurret::RotateLowerBody(float DeltaRotation)
{
	if (LowerBodyMeshComp == nullptr)
	{
		CP_LOG(Warning, TEXT("LowerBodyMeshComp == nullptr"));
		return;
	}

	LowerBodyMeshComp->AddLocalRotation(FRotator(0, DeltaRotation, 0));
}
