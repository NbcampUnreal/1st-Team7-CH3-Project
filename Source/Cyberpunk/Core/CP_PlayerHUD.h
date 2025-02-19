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

    // HUD 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHUD(int32 Wave, const FString& WeaponName, int32 Ammo, int32 Health, int32 EnemiesRemaining);

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
