#include "Character/CP_Emeny.h"

ACP_Emeny::ACP_Emeny()
{
}

void ACP_Emeny::BeginPlay()
{
	Super::BeginPlay();
}

float ACP_Emeny::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_Emeny::Die()
{
	Super::Die();
}
