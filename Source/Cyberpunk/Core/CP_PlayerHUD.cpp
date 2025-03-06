#include "CP_PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Math/Color.h" // FLinearColor와 색상 보간을 위해 필요
#include "Guns/CP_Guns.h" // ACP_Guns 클래스 사용을 위해 필요

UCP_PlayerHUD::UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UCP_PlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();
    if (WaveText) WaveText->SetText(FText::AsNumber(0));
    //if (WeaponNameText) WeaponNameText->SetText(FText::FromString("No Weapon"));
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
        // 현재 탄약 수 텍스트 업데이트
        AmmoText->SetText(FText::AsNumber(Ammo));

        // 탄약 비율 계산 (0.0 ~ 1.0)
        float ammoRatio = static_cast<float>(Ammo);

        // 흰색에서 빨간색으로 색상 보간
        FLinearColor newColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor::Red, 1.0f - ammoRatio);

        // 색상 적용
        AmmoText->SetColorAndOpacity(newColor);
    }
}

void UCP_PlayerHUD::UpdateMaxAmmo(int32 MaxAmmo)
{
    if (MaxAmmoText)
    {
        MaxAmmoText->SetText(FText::AsNumber(MaxAmmo)); // 최대 탄약량 업데이트
    }
}

void UCP_PlayerHUD::UpdateHealth(int32 Health, int32 MaxHealth)
{
    if (HealthText)
    {
        // 체력 텍스트 업데이트
        HealthText->SetText(FText::AsNumber(Health));

        // 체력 비율 계산 (0.0 ~ 1.0)
        float healthRatio = static_cast<float>(Health) / static_cast<float>(MaxHealth);

        // 흰색에서 빨간색으로 색상 보간
        FLinearColor newColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor::Red, 1.0f - healthRatio);

        // 색상 적용
        HealthText->SetColorAndOpacity(newColor);
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

void SomeFunctionToUpdateHUD(UCP_PlayerHUD* PlayerHUD, ACP_Guns* Guns)
{
    if (PlayerHUD && Guns)
    {
        int32 CurrentAmmo = Guns->AmmoCount;
        int32 MaxAmmo = Guns->MaxAmmo;

        PlayerHUD->UpdateAmmo(CurrentAmmo);
        PlayerHUD->UpdateMaxAmmo(MaxAmmo);
    }
}