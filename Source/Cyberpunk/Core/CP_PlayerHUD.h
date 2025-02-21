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

    // ���� ������Ʈ �Լ���
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateWave(int32 Wave);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateWeaponName(const FString& WeaponName);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateAmmo(int32 Ammo);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateMaxAmmo(int32 MaxAmmo); // �ִ� ź�෮ ������Ʈ �Լ� �߰�

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealth(int32 Health);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateEnemiesRemaining(int32 EnemiesRemaining);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateKillCount(int32 KillCount); // ųī��Ʈ ������Ʈ �Լ� �߰�

protected:
    virtual void NativeConstruct() override;

    // UMG ���� ���ε�
    UPROPERTY(meta = (BindWidget))
    UTextBlock* WaveText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* WeaponNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AmmoText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MaxAmmoText; // �ִ� ź�෮ �ؽ�Ʈ ��� �߰�

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* EnemiesRemainingText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillCountText; // ųī��Ʈ �ؽ�Ʈ ��� �߰�
};