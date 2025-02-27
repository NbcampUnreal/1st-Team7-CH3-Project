// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "CP_PlayerController.h"

ACP_Player::ACP_Player()
{
	SpringArmLength = 300.f;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = SpringArmLength;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
}

void ACP_Player::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerInventory)
	{
		PlayerInventory = NewObject<UCP_Inventory>(this);
		UE_LOG(LogTemp, Log, TEXT("[ACP_Player] PlayerInventory created!"));
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		ACP_PlayerController* PlayerController = Cast<ACP_PlayerController>(PC);
		if (PlayerController && PlayerController->InventoryWidget)
		{
			InventoryWidget = PlayerController->InventoryWidget;
			UE_LOG(LogTemp, Log, TEXT("[ACP_Player] InventoryWidget success!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[ACP_Player] InventoryWidget fail!"));
		}
	}
}




void ACP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACP_Player::PickupItem(ECP_ItemType ItemType, const FString& Name, UTexture2D* Icon)
{
	if (PlayerInventory)
	{
		FCP_ItemInfo NewItem;
		NewItem.ItemType = ItemType;
		NewItem.ItemName = Name;
		NewItem.ItemIcon = Icon;

		PlayerInventory->AddItem(NewItem);

		if (InventoryWidget)
		{
			InventoryWidget->UpdateInventory(PlayerInventory->GetInventoryItems());
		}
	}
}