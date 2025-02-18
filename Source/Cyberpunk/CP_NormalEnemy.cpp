#include "CP_NormalEnemy.h"

ACP_NormalEnemy::ACP_NormalEnemy()
{
}

void ACP_NormalEnemy::BeginPlay()
{
	Super::BeginPlay();
}

float ACP_NormalEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return NewDamage;
}

void ACP_NormalEnemy::Die()
{
	Super::Die();
}
