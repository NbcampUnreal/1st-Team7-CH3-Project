// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"
#include "Inventory/CP_Inventory.h"
#include "Inventory/CP_InventoryWidget.h"
#include "Guns/CP_Guns.h"
#include "CP_Player.generated.h"

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
};
