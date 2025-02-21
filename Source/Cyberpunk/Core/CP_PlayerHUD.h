#pragma once

#include "CoreMinimal.h"
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
    void UpdateAmmo(int32 Ammo);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealth(int32 Health);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateEnemiesRemaining(int32 EnemiesRemaining);

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
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* EnemiesRemainingText;
};