// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CP_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCP_InventoryWidget;
class UCP_CraftingMenuWidget;
class ACP_Guns;
class ACP_PlayerCharacter;

UCLASS()
class CYBERPUNK_API ACP_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACP_PlayerController();

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void ToggleInventory();

	UFUNCTION()
	void ToggleCraftingMenu();

	UFUNCTION()
	void ToggleLight();  

	UFUNCTION()
	void Reload();  

	UFUNCTION()
	void Fire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* StrafeAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ToggleLightAction;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ReloadAction;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCP_InventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UCP_InventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCP_CraftingMenuWidget> CraftingMenuClass;

	UPROPERTY()
	UCP_CraftingMenuWidget* CraftingMenuWidget;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CraftingMenuAction;

};
