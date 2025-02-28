#include "Character/CP_PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CP_InventoryWidget.h"
#include "Character/CP_CraftingMenuWidget.h"

ACP_PlayerController::ACP_PlayerController()
    : InputMappingContext(nullptr)
    , MoveAction(nullptr)
    , LookAction(nullptr)
    , JumpAction(nullptr)
    , CrouchAction(nullptr)
    , AimAction(nullptr)
    , SprintAction(nullptr)
    , StrafeAction(nullptr)
    , CraftingMenuAction(nullptr)
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
    if (CraftingMenuClass)
    {
        CraftingMenuWidget = CreateWidget<UCP_CraftingMenuWidget>(this, CraftingMenuClass);
        if (CraftingMenuWidget)
        {
            CraftingMenuWidget->AddToViewport();
            CraftingMenuWidget->SetVisibility(ESlateVisibility::Collapsed);UE_LOG(LogTemp, Warning, TEXT("CraftingMenuWidget created and added to viewport"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create CraftingMenuWidget"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CraftingMenuClass is not set"));
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
        if (CraftingMenuAction)
        {
            EnhancedInput->BindAction(CraftingMenuAction, ETriggerEvent::Triggered, this, &ACP_PlayerController::ToggleCraftingMenu);
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

void ACP_PlayerController::ToggleCraftingMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("ToggleCraftingMenu called"));

    if (CraftingMenuWidget)
    {
        if (CraftingMenuWidget->IsVisible())
        {
            CraftingMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
            SetShowMouseCursor(false);
            SetInputMode(FInputModeGameOnly()); // 게임 모드로 복귀
            UE_LOG(LogTemp, Warning, TEXT("CraftingMenuWidget set to Collapsed"));
        }
        else
        {
            CraftingMenuWidget->SetVisibility(ESlateVisibility::Visible);
            SetShowMouseCursor(true);
            SetInputMode(FInputModeGameAndUI()); // UI와 게임 동시 조작 가능
            UE_LOG(LogTemp, Warning, TEXT("CraftingMenuWidget set to Visible"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CraftingMenuWidget is not valid"));
    }
}