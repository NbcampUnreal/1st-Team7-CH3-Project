#include "Character/CP_Enemy.h"

ACP_Enemy::ACP_Enemy()
{
}

void ACP_Enemy::BeginPlay()
{
	Super::BeginPlay();
}

float ACP_Enemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_Enemy::Die()
{
	Super::Die();
}
