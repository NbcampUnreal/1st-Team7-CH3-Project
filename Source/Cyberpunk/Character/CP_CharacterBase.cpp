#include "Character/CP_CharacterBase.h"

#include "Cyberpunk.h"

ACP_CharacterBase::ACP_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACP_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetGenericTeamId((uint8)TeamType);
	
	USkeletalMeshComponent* MeshComp = GetMesh();
	TArray<UMaterialInterface*> OriginalMaterials = MeshComp->GetMaterials();

	for (int i = 0; i < OriginalMaterials.Num(); ++i)
	{
		UMaterialInterface* OriginalMaterial = OriginalMaterials[i];
		if (OriginalMaterial == nullptr)
		{
			CP_LOG(Warning, TEXT("OriginalMaterial == nullptr, Index : %d"), i);
			continue;
		}

		UMaterialInstanceDynamic* Dynamic = UMaterialInstanceDynamic::Create(OriginalMaterial, MeshComp);
		CurrentDissolveMaterialInstanceArray.Emplace(MoveTemp(Dynamic));
		MeshComp->SetMaterial(i, CurrentDissolveMaterialInstanceArray.Last());
	}

}

void ACP_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACP_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACP_CharacterBase::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	TeamId = TeamID;
}

FGenericTeamId ACP_CharacterBase::GetGenericTeamId() const
{
	return TeamId;
}

float ACP_CharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	// 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("[ACP_CharacterBase] TakeDamage called - Damage: %f, Causer: %s"),
		Damage,
		DamageCauser ? *DamageCauser->GetName() : TEXT("Unknown"));

	return NewDamage;
}

void ACP_CharacterBase::Dissolve(const float InDissolveTime)
{
	GetWorld()->GetTimerManager().SetTimer(DissolveTimerHandle, [&]()
		{
			if (::IsValid(GetWorld()) == false)
			{
				DissolveTimerHandle.Invalidate();
				return;
			}

			if (::IsValid(this) == false)
			{
				GetWorldTimerManager().ClearTimer(DissolveTimerHandle);
				DissolveTimerHandle.Invalidate();
				return;
			}

			float CurrentDissolveBorder = DissolveProgress * DissolveSpeed;
			if (CurrentDissolveBorder > MaxDissolveBorder)
			{
				GetWorldTimerManager().ClearTimer(DissolveTimerHandle);
				DissolveTimerHandle.Invalidate();
				return;
			}

			int32 MaterialCount = CurrentDissolveMaterialInstanceArray.Num();
			USkeletalMeshComponent* MeshComp = GetMesh();

			for (int i = 0; i < MaterialCount; ++i)
			{
				UMaterialInstanceDynamic* Dynamic = CurrentDissolveMaterialInstanceArray[i];

				if (Dynamic == nullptr)
				{
					CP_LOG(Warning, TEXT("Dynamic == nullptr, Index : %d"), i);
					continue;
				}

				Dynamic->SetScalarParameterValue(TEXT("Border"), CurrentDissolveBorder);
				Dynamic->GetScalarParameterValue(TEXT("Border"), CurrentDissolveBorder);
			}

			DissolveProgress += 1;

		}, 0.02f, true, 0);

}

void ACP_CharacterBase::Dissolve()
{
	Dissolve(DissolveTime);
}

void ACP_CharacterBase::Die()
{
	if (bIsDead)
	{
		return;
	}
	
	CP_LOG(Log, TEXT("%s is Dead."), *GetName());
	bIsDead = true;

	if (bShouldUseDissolve)
	{
		Dissolve();
	}
}

bool ACP_CharacterBase::IsDead()
{
	return bIsDead;
}

int32 ACP_CharacterBase::GetMaxHP()
{
	return MaxHp;
}

int32 ACP_CharacterBase::GetCurrentHp()
{
	return CurrentHp;
}

ETeamType ACP_CharacterBase::GetTeamType()
{
	return TeamType;
}
