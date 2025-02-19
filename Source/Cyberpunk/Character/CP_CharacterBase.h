#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CP_CharacterBase.generated.h"

UCLASS()
class CYBERPUNK_API ACP_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ACP_CharacterBase();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	// UGameplayStatics::ApplyDamage를 호출하면 이 함수가 대신해서 호출된다.
	// 데미지를 주고싶을 때 TakeDamage를 직접 호출해도 되지만 UGameplayStatics::ApplyDamage로 호출하는 것을 권장.
	// 참고로 UGameplayStatics는 "Kismet/GameplayStatics.h" 헤더파일 필요
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void Die();

protected:

	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 MaxHp = 1;

	// 버프 효과 고려해서 CurrentHp, BaseHp 나눔.
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 CurrentHp = 1;

	// 순수 체력을 의미
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseHp = 1;

	// 버프 효과 고려해서 Current Armor, Base Armor 나눔.
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 CurrentArmor = 1;

	// 순수 방어력을 의미
	UPROPERTY(EditAnywhere, Category = "CPCharacter")
	int32 BaseArmor = 1;

};
