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
    if (MaxAmmoText) MaxAmmoText->SetText(FText::AsNumber(0)); // 최대 탄약량 초기값 설정
    if (HealthText) HealthText->SetText(FText::AsNumber(100));
    if (EnemiesRemainingText) EnemiesRemainingText->SetText(FText::AsNumber(0));
    if (KillCountText) KillCountText->SetText(FText::AsNumber(0)); // 킬카운트 초기값 설정
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

void UCP_PlayerHUD::UpdateMaxAmmo(int32 MaxAmmo)
{
    if (MaxAmmoText)
    {
        MaxAmmoText->SetText(FText::AsNumber(MaxAmmo)); // 최대 탄약량 업데이트
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

void UCP_PlayerHUD::UpdateKillCount(int32 KillCount)
{
    if (KillCountText)
    {
        KillCountText->SetText(FText::AsNumber(KillCount)); // 킬카운트 업데이트
    }
}