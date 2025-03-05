#include "CP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "CP_PlayerController.h"
#include "EngineUtils.h"
#include "Cyberpunk.h"
#include "Kismet/GameplayStatics.h"

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
	bShouldUseDissolve = false;
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
		if (PlayerController)
		{
			if (PlayerController->InventoryWidget)
			{
				InventoryWidget = PlayerController->InventoryWidget;
				InventoryWidget->SetInventoryReference(PlayerInventory);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[ACP_Player] InventoryWidget is nullptr!"));
			}

			if (PlayerController->CraftingMenuWidget)
			{
				PlayerController->CraftingMenuWidget->SetInventoryReference(PlayerInventory);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[ACP_Player] CraftingMenuWidget is nullptr!"));
			}
		}
	}

	if (GetWorld() && DefaultGunClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		ACP_Guns* SpawnedGun = GetWorld()->SpawnActor<ACP_Guns>(DefaultGunClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (SpawnedGun)
		{
			SetEquippedGun(SpawnedGun);
			UE_LOG(LogTemp, Log, TEXT("[ACP_Player] Spawned default gun: %s"), *DefaultGunClass->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[ACP_Player] Failed to spawn default gun!"));
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

float ACP_Player::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	int32 HpAfterDamage = CurrentHp - NewDamage;

	CurrentHp = FMath::Clamp(HpAfterDamage, 0, HpAfterDamage);

	OnHpChangedDelegate.Broadcast(CurrentHp, MaxHp);

	if (CurrentHp == 0)
	{
		Die();
	}

	return NewDamage;
}

void ACP_Player::Heal(int HealAmount)
{
	CurrentHp += HealAmount;
	CurrentHp = FMath::Clamp(CurrentHp, 0, MaxHp);
	OnHpChangedDelegate.Broadcast(CurrentHp, MaxHp);
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

		//플레이어 인벤토리를 총에 설정
		if (PlayerInventory)
		{
			EquippedGun->SetInventory(PlayerInventory);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[ACP_Player] ERROR: PlayerInventory is nullptr!"));
		}
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

void ACP_Player::Die()
{
	Super::Die();
	ActivateRagdoll();
}

void ACP_Player::ActivateRagdoll()
{
	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh == nullptr)
	{
		CP_LOG(Error, TEXT("MyMesh == nullptr, Name : "), *GetName());
		return;
	}

	MyMesh->SetAnimInstanceClass(nullptr);
	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetCollisionProfileName(TEXT("Ragdoll"));
}
