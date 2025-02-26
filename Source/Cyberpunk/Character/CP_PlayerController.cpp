// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CP_PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CP_InventoryWidget.h"

ACP_PlayerController::ACP_PlayerController()
	: InputMappingContext(nullptr)
	, MoveAction(nullptr)
	, LookAction(nullptr)
	, JumpAction(nullptr)
	, CrouchAction(nullptr)
	, AimAction(nullptr)
	, SprintAction(nullptr)
	, StrafeAction(nullptr)
{
}

void ACP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UCP_InventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}



void ACP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (InventoryAction)
		{
			EnhancedInput->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ACP_PlayerController::ToggleInventory);
		}
	}
}

void ACP_PlayerController::ToggleInventory()
{
	if (InventoryWidget)
	{
		if (InventoryWidget->IsVisible())
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
			SetShowMouseCursor(false);
			SetInputMode(FInputModeGameOnly()); // 게임 모드로 복귀
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			SetShowMouseCursor(true);
			SetInputMode(FInputModeGameAndUI()); // UI와 게임 동시 조작 가능
		}
	}
}