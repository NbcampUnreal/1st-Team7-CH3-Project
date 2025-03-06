#include "Guns/CP_CurveProjectile.h"

#include "Cyberpunk.h"
#include "Character/CP_CharacterBase.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Components/DecalComponent.h"

ACP_CurveProjectile::ACP_CurveProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACP_CurveProjectile::OnBeginOverlap);
	SetRootComponent(SphereCollisionComponent);
}

void ACP_CurveProjectile::BeginPlay()
{
	Super::BeginPlay();

	FHitResult HitResult;
	FVector Start = TargetPoint;
	FVector End = TargetPoint + FVector::DownVector * 500;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams);
	if (bIsHit && DecalActorClass)
	{
		TargetPoint = HitResult.Location;
		CurrentDecal = GetWorld()->SpawnActor<AActor>(DecalActorClass, TargetPoint, FRotator::ZeroRotator);
	}
}


void ACP_CurveProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentProgress >= 1)
	{
		OnBeginOverlap(nullptr, nullptr, nullptr, 0, false, FHitResult());
		return;
	}

	FVector CurrentPoint = QuadraticBezierInterp(StartPoint, ControlPoint, TargetPoint, CurrentProgress);
	SetActorLocation(CurrentPoint);
	CurrentProgress += DeltaTime * Speed;
	CurrentProgress = FMath::Clamp(CurrentProgress, 0, 1);
}

void ACP_CurveProjectile::InitProjectile(const FVector& NewTargetPoint, float NewSpeed, AActor* NewIgnoredActor)
{
	StartPoint = GetActorLocation();
	TargetPoint = NewTargetPoint;
	Speed = NewSpeed;
	IgnoredActor = NewIgnoredActor;

	FVector DirectrionToTarget = TargetPoint - StartPoint;
	float DistanceToTarget = DirectrionToTarget.Length();
	DirectrionToTarget.Normalize();

	FVector CenterPosition = StartPoint + DirectrionToTarget * DistanceToTarget / 2;

	float Height = DistanceToTarget / 2;
	ControlPoint = CenterPosition + FVector::UpVector * Height;
	ControlPoint.Z = FMath::Clamp(ControlPoint.Z, 0, MaxHeight);
	CurrentProgress = 0.0f;
}

void ACP_CurveProjectile::InitProjectile(const FVector& NewTargetPoint, AActor* NewIgnoredActor)
{
	InitProjectile(NewTargetPoint, Speed, NewIgnoredActor);
}

FVector ACP_CurveProjectile::QuadraticBezierInterp(const FVector& InStartPoint, const FVector& InControlPoint, const FVector& InEndPoint, float Progress)
{
	float Reverse = 1.0f - Progress;
	return Reverse * Reverse * InStartPoint + 2.0f * Reverse * Progress * InControlPoint + Progress * Progress * InEndPoint;
}

void ACP_CurveProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == IgnoredActor)
	{
		return;
	}

	if (HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorTransform());
	}

	if (CurrentDecal)
	{
		CurrentDecal->Destroy();
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(IgnoredActor);

	bool bIsHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(ExplosionRadius), QueryParams);

	if (bIsHit == false)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 8, FColor::Red, false, 1);
		Destroy();
		return;
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 8, FColor::Green, false, 3);
	
	TSet<ACP_CharacterBase*> DamagedCharacter;
	for (auto& OverlapResult : OverlapResults)
	{
		ACP_CharacterBase* Character = Cast<ACP_CharacterBase>(OverlapResult.GetActor());
		if (Character == nullptr || DamagedCharacter.Contains(Character))
		{
			continue;
		}

		DamagedCharacter.Add(Character);

		FPointDamageEvent PointDamageEvent;
		Character->TakeDamage(ProjectileDamage, PointDamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
		CP_LOG(Log, TEXT("%s is Damaged by %s, Damage : %f"), *Character->GetName(), *GetOwner()->GetName(), ProjectileDamage);
	}

	Destroy();
}

