#include "CP_CraftingMenuWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Guns/CP_BarrelInfo.h"
#include "Guns/CP_TriggerInfo.h"
#include "Guns/CP_BodyInfo.h"

UCP_CraftingMenuWidget::UCP_CraftingMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCP_CraftingMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BarrelButton1)
    {
        BarrelButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton1Clicked);
    }

    if (BarrelButton2)
    {
        BarrelButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton2Clicked);
    }

    if (BarrelButton3)
    {
        BarrelButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBarrelButton3Clicked);
    }

    if (TriggerButton1)
    {
        TriggerButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton1Clicked);
    }

    if (TriggerButton2)
    {
        TriggerButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton2Clicked);
    }

    if (TriggerButton3)
    {
        TriggerButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnTriggerButton3Clicked);
    }

    if (BodyButton1)
    {
        BodyButton1->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton1Clicked);
    }

    if (BodyButton2)
    {
        BodyButton2->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton2Clicked);
    }

    if (BodyButton3)
    {
        BodyButton3->OnClicked.AddDynamic(this, &UCP_CraftingMenuWidget::OnBodyButton3Clicked);
    }
}

void UCP_CraftingMenuWidget::OnBarrelButton1Clicked()
{
    FString Name = TEXT("BarrelBeam");
    FString Description = TEXT("This is the first barrel of the gun.");
    // 실제 CP_BarrelInfo에서 정보필요
    // Name = CP_BarrelInfo::GetName(1);
    // Description = CP_BarrelInfo::GetDescription(1);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBarrelButton2Clicked()
{
    FString Name = TEXT("BarrelBeamScatter");
    FString Description = TEXT("This is the second barrel of the gun.");
    // 실제 CP_BarrelInfo에서 정보필요
    // Name = CP_BarrelInfo::GetName(2);
    // Description = CP_BarrelInfo::GetDescription(2);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBarrelButton3Clicked()
{
    FString Name = TEXT("BarrelBulletScatter");
    FString Description = TEXT("This is the third barrel of the gun.");
    // 실제 CP_BarrelInfo에서 정보필요
    // Name = CP_BarrelInfo::GetName(3);
    // Description = CP_BarrelInfo::GetDescription(3);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnTriggerButton1Clicked()
{
    FString Name = TEXT("Trigger 1");
    FString Description = TEXT("This is the first trigger of the gun.");
    // 실제 CP_TriggerInfo에서 정보필요
    // Name = CP_TriggerInfo::GetName(1);
    // Description = CP_TriggerInfo::GetDescription(1);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnTriggerButton2Clicked()
{
    FString Name = TEXT("Trigger 2");
    FString Description = TEXT("This is the second trigger of the gun.");
    // 실제 CP_TriggerInfo에서 정보필요
    // Name = CP_TriggerInfo::GetName(2);
    // Description = CP_TriggerInfo::GetDescription(2);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnTriggerButton3Clicked()
{
    FString Name = TEXT("Trigger 3");
    FString Description = TEXT("This is the third trigger of the gun.");
    // 실제 CP_TriggerInfo에서 정보필요
    // Name = CP_TriggerInfo::GetName(3);
    // Description = CP_TriggerInfo::GetDescription(3);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBodyButton1Clicked()
{
    FString Name = TEXT("Body 1");
    FString Description = TEXT("This is the first body of the gun.");
    // 실제 CP_BodyInfo에서 정보필요
    // Name = CP_BodyInfo::GetName(1);
    // Description = CP_BodyInfo::GetDescription(1);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBodyButton2Clicked()
{
    FString Name = TEXT("Body 2");
    FString Description = TEXT("This is the second body of the gun.");
    // 실제 CP_BodyInfo에서 정보필요
    // Name = CP_BodyInfo::GetName(2);
    // Description = CP_BodyInfo::GetDescription(2);
    UpdateItemInfo(Name, Description);
}

void UCP_CraftingMenuWidget::OnBodyButton3Clicked()
{
    FString Name = TEXT("Body 3");
    FString Description = TEXT("This is the third body of the gun.");
    // 실제 CP_BodyInfo에서 정보필요
    // Name = CP_BodyInfo::GetName(3);
    // Description = CP_BodyInfo::GetDescription(3);
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
