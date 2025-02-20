#include "Character/CP_CharacterBase.h"

#include "Cyberpunk.h"

ACP_CharacterBase::ACP_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACP_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACP_CharacterBase::Tick(float DeltaTime)
{
}

void ACP_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACP_CharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CP_LOG(Log, TEXT("%s is damaged by %s, Damage : %f"), *GetName(), *DamageCauser->GetName(), NewDamage);

	return NewDamage;
}

void ACP_CharacterBase::Die()
{
	CP_LOG(Log, TEXT("%s is Dead."));
	bIsDead = true;
}

bool ACP_CharacterBase::IsDead()
{
	return bIsDead;
}

