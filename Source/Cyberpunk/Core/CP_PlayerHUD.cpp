#include "CP_PlayerHUD.h"
#include "Components/TextBlock.h"

UCP_PlayerHUD::UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UCP_PlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

}

void UCP_PlayerHUD::UpdateHUD(int32 Wave, const FString& WeaponName, int32 Ammo, int32 Health, int32 EnemiesRemaining)
{
    if (WaveText)
    {
        WaveText->SetText(FText::AsNumber(Wave));
    }
    if (WeaponNameText)
    {
        WeaponNameText->SetText(FText::FromString(WeaponName));
    }
    if (AmmoText)
    {
        AmmoText->SetText(FText::AsNumber(Ammo));
    }
    if (HealthText)
    {
        HealthText->SetText(FText::AsNumber(Health));
    }
    if (EnemiesRemainingText)
    {
        EnemiesRemainingText->SetText(FText::AsNumber(EnemiesRemaining));
    }
}
