// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"
#include "Inventory/CP_Inventory.h"
#include "Inventory/CP_InventoryWidget.h"
#include "CP_CraftingMenuWidget.h"
#include "Guns/CP_Guns.h"
#include "Components/CapsuleComponent.h"
#include "CP_Player.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, int, CurrentHp, int, MaxHp);

class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class CYBERPUNK_API ACP_Player : public ACP_CharacterBase
{
	GENERATED_BODY()
public:

	ACP_Player();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Heal(int HealAmount);
	void FireWeapon();
	void ReloadWeapon();
	void ToggleTactical();
	
	FOnHpChangedDelegate OnHpChangedDelegate;

public:
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SpringArmLength;

	UPROPERTY()
	UCP_Inventory* PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UCP_InventoryWidget* InventoryWidget;

	void PickupItem(ECP_ItemType ItemType, const FString& Name, UTexture2D* Icon);

	UPROPERTY()
	ACP_Guns* EquippedGun;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetEquippedGun(ACP_Guns* NewGun);

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void ActivateTimeAccelerator();

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TSubclassOf<ACP_Guns> DefaultGunClass;  

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void CreateTurret();

protected:

	void SetActivateTimeAccelerator(bool bShouldActivate);
	virtual void Die() override;

	void ActivateRagdoll();

protected:

	UPROPERTY(EditAnywhere, Category = "Spell")
	float TimeAcceleratorDuration = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Spell")
	float TimeAcceleratorEffect = 0.1f;

	bool bIsTimeAcceleratorActivated = false;

	UPROPERTY(EditAnywhere, Category = "Spell")
	TSubclassOf<class ACP_PlayerTurret> PlayerTurretClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	TObjectPtr<UNiagaraComponent> TimeAcceleratorVFX;

private:

	FTimerHandle TimeAcceleratorTimerHandle;
};
