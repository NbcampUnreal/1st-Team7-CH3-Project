#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CP_CraftingMenuWidget.generated.h"

UCLASS()
class CYBERPUNK_API UCP_CraftingMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UCP_CraftingMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeConstruct() override;

    // UMG À§Á¬ ¹ÙÀÎµù
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* BarrelButton3;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* TriggerButton3;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton1;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton2;
    UPROPERTY(meta = (BindWidget))
    UButton* BodyButton3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemName;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemDescription;

private:
    UFUNCTION()
    void OnBarrelButton1Clicked();
    UFUNCTION()
    void OnBarrelButton2Clicked();
    UFUNCTION()
    void OnBarrelButton3Clicked();
    UFUNCTION()
    void OnTriggerButton1Clicked();
    UFUNCTION()
    void OnTriggerButton2Clicked();
    UFUNCTION()
    void OnTriggerButton3Clicked();
    UFUNCTION()
    void OnBodyButton1Clicked();
    UFUNCTION()
    void OnBodyButton2Clicked();
    UFUNCTION()
    void OnBodyButton3Clicked();

    void UpdateItemInfo(const FString& Name, const FString& Description);
};
