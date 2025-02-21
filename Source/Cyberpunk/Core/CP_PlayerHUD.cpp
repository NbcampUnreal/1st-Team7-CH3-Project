#include "CP_PlayerHUD.h"
#include "Components/TextBlock.h"

UCP_PlayerHUD::UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UCP_PlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();
    if (WaveText) WaveText->SetText(FText::AsNumber(0));
    if (WeaponNameText) WeaponNameText->SetText(FText::FromString("No Weapon"));
    if (AmmoText) AmmoText->SetText(FText::AsNumber(0));
    if (HealthText) HealthText->SetText(FText::AsNumber(100));
    if (EnemiesRemainingText) EnemiesRemainingText->SetText(FText::AsNumber(0));
}

void UCP_PlayerHUD::UpdateWave(int32 Wave)
{
    if (WaveText)
    {
        WaveText->SetText(FText::AsNumber(Wave));
    }
}

void UCP_PlayerHUD::UpdateWeaponName(const FString& WeaponName)
{
    if (WeaponNameText)
    {
        WeaponNameText->SetText(FText::FromString(WeaponName));
    }
}

void UCP_PlayerHUD::UpdateAmmo(int32 Ammo)
{
    if (AmmoText)
    {
        AmmoText->SetText(FText::AsNumber(Ammo));
    }
}

void UCP_PlayerHUD::UpdateHealth(int32 Health)
{
    if (HealthText)
    {
        HealthText->SetText(FText::AsNumber(Health));
    }
}

void UCP_PlayerHUD::UpdateEnemiesRemaining(int32 EnemiesRemaining)
{
    if (EnemiesRemainingText)
    {
        EnemiesRemainingText->SetText(FText::AsNumber(EnemiesRemaining));
    }
}

