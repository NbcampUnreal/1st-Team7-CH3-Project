#include "Character/CP_Enemy.h"

#include "Cyberpunk.h"
#include "Core/CP_GameState.h"
#include "Core/CP_PlayerHUD.h"
#include "Core/CP_GameInstance.h"

#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

int32 ACP_Enemy::AvoidanceUID = 0;

ACP_Enemy::ACP_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	TeamType = ETeamType::EnemyTeam;

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	MovementComp->bUseRVOAvoidance = true;
	MovementComp->AvoidanceWeight = 1.0f;
	MovementComp->AvoidanceConsiderationRadius = 100.0f;
}

void ACP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();

	MovementComp->SetRVOAvoidanceUID(AvoidanceUID);
	AvoidanceUID++;
	MovementComp->SetAvoidanceGroup((AvoidanceUID % 31));
	//CP_LOG(Warning, TEXT(" AvoidanceId : %d, Group : %d"), MovementComp->AvoidanceUID, MovementComp->GetAvoidanceGroupMask());
}

float ACP_Enemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CP_LOG(Log, TEXT("Damaged Enemy : %s"), *GetName());

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

void ACP_Enemy::AttackNormal()
{
}

void ACP_Enemy::Die()
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


	UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance == nullptr)
	{
		CP_LOG(Warning, TEXT("GameInstance == nullptr"));
		return;
	}
	GameInstance->Decrease_AI();

	OnEnemyDeadDelegate.Broadcast(GetActorLocation());
}

void ACP_Enemy::BreakBones(FHitResult HitInfo)
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

float ACP_Enemy::GetAttackRange()
{
	return AttackRange;
}


