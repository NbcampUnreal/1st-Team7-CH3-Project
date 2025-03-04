#include "CP_CraftingMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CP_Player.h"


UCP_CraftingMenuWidget::UCP_CraftingMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCP_CraftingMenuWidget::SetInventoryReference(UCP_Inventory* Inventory)
{
    InventoryRef = Inventory;
    if (InventoryRef)
    {
        UE_LOG(LogTemp, Log, TEXT("[UCP_CraftingMenuWidget] InventoryRef successfully set"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[UCP_CraftingMenuWidget] InventoryRef is nullptr!"));
    }
}


void UCP_CraftingMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ButtonPartMap.Add(BarrelButton1, "SK_BarrelBeam");
    ButtonPartMap.Add(BarrelButton2, "SK_BarrelBeamScatter");
    ButtonPartMap.Add(BarrelButton3, "SK_BarrelBulletScatter");
    ButtonPartMap.Add(TriggerButton1, "SK_TriggerAuto");
    ButtonPartMap.Add(TriggerButton2, "SK_TriggerBurst");
    ButtonPartMap.Add(TriggerButton3, "SK_StockStandard");
    ButtonPartMap.Add(BodyButton1, "SK_BodyTesla");
    ButtonPartMap.Add(BodyButton2, "SK_BodyNormal");
    ButtonPartMap.Add(BodyButton3, "SK_BodyFire");

    if (BarrelButton1) BarrelButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton1Clicked);
    if (BarrelButton2) BarrelButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton2Clicked);
    if (BarrelButton3) BarrelButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton3Clicked);
    if (TriggerButton1) TriggerButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton1Clicked);
    if (TriggerButton2) TriggerButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton2Clicked);
    if (TriggerButton3) TriggerButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton3Clicked);
    if (BodyButton1) BodyButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton1Clicked);
    if (BodyButton2) BodyButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton2Clicked);
    if (BodyButton3) BodyButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton3Clicked);
}



FReply UCP_CraftingMenuWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("[UCP_CraftingMenuWidget] Right-click detected"));

        for (auto& Pair : ButtonPartMap)
        {
            UButton* Button = Pair.Key;
            if (Button && Button->IsHovered()) // 현재 마우스가 버튼 위에 있는지 확인
            {
                OnRightClickPart(Button);
                return FReply::Handled();
            }
        }
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCP_CraftingMenuWidget::OnRightClickPart(UButton* ClickedButton)
{
    if (!ClickedButton || !ButtonPartMap.Contains(ClickedButton))
    {
        HandleCraftingFail();
        return;
    }

    FString PartName = ButtonPartMap[ClickedButton];
    int32 GearCost = 0;
    EGunPartType PartType;

    if (PartName.Contains("Barrel"))
    {
        ACP_BarrelInfo* TempBarrel = NewObject<ACP_BarrelInfo>();
        TempBarrel->Initialize(PartName);
        GearCost = TempBarrel->GetGearCost();
        PartType = EGunPartType::Barrel;
    }
    else if (PartName.Contains("Trigger"))
    {
        ACP_TriggerInfo* TempTrigger = NewObject<ACP_TriggerInfo>();
        TempTrigger->Initialize(PartName);
        GearCost = TempTrigger->GetGearCost();
        PartType = EGunPartType::Trigger;
    }
    else if (PartName.Contains("Body"))
    {
        ACP_BodyInfo* TempBody = NewObject<ACP_BodyInfo>();
        TempBody->Initialize(PartName);
        GearCost = TempBody->GetGearCost();
        PartType = EGunPartType::Body;
    }
    else
    {
        HandleCraftingFail();
        return;
    }

    if (!InventoryRef)
    {
        HandleCraftingFail();
        return;
    }

    int32 CurrentGearCount = InventoryRef->GetItemCount("Gear");

    
    if (CurrentGearCount < GearCost)
    {
        HandleCraftingFail();
        return;
    }

  
    InventoryRef->ReduceItemCountByName("Gear", GearCost);
   
    ACP_Player* Player = Cast<ACP_Player>(InventoryRef->GetOwner());
    if (Player && Player->EquippedGun)
    {
        Player->EquippedGun->EquipPart(PartName, PartType);
        PlayEquipSound(true);
        
    }

}



void UCP_CraftingMenuWidget::OnBarrelButton1Clicked()
{
    ACP_BarrelInfo* Barrel = NewObject<ACP_BarrelInfo>();
    Barrel->Initialize("SK_BarrelBeam");

    FString Name = Barrel->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nHitscan: %s\nGear Cost: %d"),
        Barrel->GetDamage(),
        Barrel->IsHitscan() ? TEXT("Yes") : TEXT("No"),
        Barrel->GetGearCost());  

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::PlayEquipSound(bool bSuccess)
{
    if (bSuccess && EquipSuccessSound)
    {
        UGameplayStatics::PlaySound2D(this, EquipSuccessSound);
    }
    else if (!bSuccess && EquipFailSound)
    {
        UGameplayStatics::PlaySound2D(this, EquipFailSound);
    }
}

void UCP_CraftingMenuWidget::OnBarrelButton2Clicked()
{
    ACP_BarrelInfo* Barrel = NewObject<ACP_BarrelInfo>();
    Barrel->Initialize("SK_BarrelBeamScatter");

    FString Name = Barrel->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nHitscan: %s\nGear Cost: %d"),
        Barrel->GetDamage(),
        Barrel->IsHitscan() ? TEXT("Yes") : TEXT("No"),
        Barrel->GetGearCost());

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBarrelButton3Clicked()
{
    ACP_BarrelInfo* Barrel = NewObject<ACP_BarrelInfo>();
    Barrel->Initialize("SK_BarrelBulletScatter");

    FString Name = Barrel->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nHitscan: %s\nGear Cost: %d"),
        Barrel->GetDamage(),
        Barrel->IsHitscan() ? TEXT("Yes") : TEXT("No"),
        Barrel->GetGearCost());

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnTriggerButton1Clicked()
{
    ACP_TriggerInfo* Trigger = NewObject<ACP_TriggerInfo>();
    Trigger->Initialize("SK_TriggerAuto");

    FString Name = Trigger->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nMagazine: %d\nGear Cost: %d"),
        Trigger->GetDamage(),
        Trigger->GetMagazineCapacity(),
        Trigger->GetGearCost());  

    UpdateItemInfo(Name, Description);
}


void UCP_CraftingMenuWidget::OnTriggerButton2Clicked()
{
    ACP_TriggerInfo* Trigger = NewObject<ACP_TriggerInfo>();
    Trigger->Initialize("SK_TriggerBurst");

    FString Name = Trigger->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nMagazine: %d\nGear Cost: %d"),
        Trigger->GetDamage(),
        Trigger->GetMagazineCapacity(),
        Trigger->GetGearCost());

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnTriggerButton3Clicked()
{
    ACP_TriggerInfo* Trigger = NewObject<ACP_TriggerInfo>();
    Trigger->Initialize("SK_StockStandard");

    FString Name = Trigger->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nMagazine: %d\nGear Cost: %d"),
        Trigger->GetDamage(),
        Trigger->GetMagazineCapacity(),
        Trigger->GetGearCost());

    UpdateItemInfo(Name, Description);
}


void UCP_CraftingMenuWidget::OnBodyButton1Clicked()
{
    ACP_BodyInfo* Body = NewObject<ACP_BodyInfo>();
    Body->Initialize("SK_BodyTesla");

    FString Name = Body->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nSpeed: %.1f\nGear Cost: %d"),
        Body->GetDamage(),
        Body->GetMovementSpeed(),
        Body->GetGearCost());

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBodyButton2Clicked()
{
    ACP_BodyInfo* Body = NewObject<ACP_BodyInfo>();
    Body->Initialize("SK_BodyNormal");

    FString Name = Body->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nSpeed: %.1f\nGear Cost: %d"),
        Body->GetDamage(),
        Body->GetMovementSpeed(),
        Body->GetGearCost());

    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBodyButton3Clicked()
{
    ACP_BodyInfo* Body = NewObject<ACP_BodyInfo>();
    Body->Initialize("SK_BodyFire");

    FString Name = Body->GetPartName();
    FString Description = FString::Printf(TEXT("Damage: %.1f\nSpeed: %.1f\nGear Cost: %d"),
        Body->GetDamage(),
        Body->GetMovementSpeed(),
        Body->GetGearCost());

    UpdateItemInfo(Name, Description);
}


void UCP_CraftingMenuWidget::UpdateItemInfo(const FString& Name, const FString& Description)
{
    if (ItemName)
    {
        ItemName->SetText(FText::FromString(Name));
    }

    if (ItemDescription)
    {
        ItemDescription->SetText(FText::FromString(Description));
    }
}

void UCP_CraftingMenuWidget::HandleCraftingFail()
{
   
    APlayerController* PC = GetOwningPlayer();
    if (PC)
    {
        TSubclassOf<UCameraShakeBase> CraftingFailShake = LoadClass<UCameraShakeBase>(
            nullptr,
            TEXT("Blueprint'/Game/Gun_BluePrint/BP_CameraShake.BP_CameraShake_C'")
        );

        if (CraftingFailShake)
        {
            PC->ClientStartCameraShake(CraftingFailShake);
            
        }
 
    }

    PlayEquipSound(false);
}
