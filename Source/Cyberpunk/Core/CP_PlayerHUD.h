#pragma once

#include "CoreMinimal.h"
#include "Guns/CP_Guns.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CP_PlayerHUD.generated.h"

UCLASS()
class CYBERPUNK_API UCP_PlayerHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UCP_PlayerHUD(const FObjectInitializer& ObjectInitializer);

    // 개별 업데이트 함수들
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateWave(int32 Wave);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateWeaponName(const FString& WeaponName);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateAmmo(int32 Ammo); // 최대 탄약 추가

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateMaxAmmo(int32 MaxAmmo); // 최대 탄약량 업데이트 함수

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealth(int32 Health, int32 MaxHealth); // 최대 체력 추가

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateEnemiesRemaining(int32 EnemiesRemaining);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateKillCount(int32 KillCount); // 킬카운트 업데이트 함수

protected:
    virtual void NativeConstruct() override;

    // UMG 위젯 바인딩
    UPROPERTY(meta = (BindWidget))
    UTextBlock* WaveText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* WeaponNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AmmoText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MaxAmmoText; // 최대 탄약량 텍스트 블록

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* EnemiesRemainingText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillCountText; // 킬카운트 텍스트 블록
};