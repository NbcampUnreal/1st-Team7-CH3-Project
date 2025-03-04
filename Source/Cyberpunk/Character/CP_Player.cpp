// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "CP_PlayerController.h"
#include "EngineUtils.h"

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

	EquippedGun = nullptr;  
}

void ACP_Player::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerInventory)
	{
		PlayerInventory = NewObject<UCP_Inventory>(this);
		if (PlayerInventory)
		{
			PlayerInventory->Initialize(this);  
		}

	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		ACP_PlayerController* PlayerController = Cast<ACP_PlayerController>(PC);
		if (PlayerController && PlayerController->InventoryWidget)
		{
			InventoryWidget = PlayerController->InventoryWidget;
		}

		if (InventoryWidget)
		{
			InventoryWidget->SetInventoryReference(PlayerInventory);
		}
	}

	if (GetWorld())
	{
		for (TActorIterator<ACP_Guns> It(GetWorld()); It; ++It)
		{
			ACP_Guns* FoundGun = *It;
			if (FoundGun)
			{
				SetEquippedGun(FoundGun);
				break;
			}
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

void ACP_Player::SetEquippedGun(ACP_Guns* NewGun)
{
	if (NewGun)
	{
		EquippedGun = NewGun;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		EquippedGun->AttachToComponent(GetMesh(), AttachmentRules, TEXT("WeaponArm"));
	}

}

void ACP_Player::ActivateTimeAccelerator()
{
	SetActivateTimeAccelerator(true);
}

void ACP_Player::SetActivateTimeAccelerator(bool bShouldActivate)
{
	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}

	bIsTimeAcceleratorActivated = bShouldActivate;

	if (bIsTimeAcceleratorActivated == false)
	{
		TimeAcceleratorTimerHandle.Invalidate();
		World->GetWorldSettings()->SetTimeDilation(1);
		CustomTimeDilation = 1;
		return;
	}

	World->GetWorldSettings()->SetTimeDilation(TimeAcceleratorEffect);
	CustomTimeDilation = 1 / TimeAcceleratorEffect;

	World->GetTimerManager().SetTimer(TimeAcceleratorTimerHandle, [this]()
		{
			if (::IsValid(GetWorld()) == false)
			{
				return;
			}

			GetWorld()->GetWorldSettings()->SetTimeDilation(1);
			CustomTimeDilation = 1;

		}, TimeAcceleratorDuration * TimeAcceleratorEffect, false);
}
