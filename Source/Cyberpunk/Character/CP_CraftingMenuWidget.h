#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Guns/CP_BarrelInfo.h"
#include "Guns/CP_TriggerInfo.h"
#include "Guns/CP_BodyInfo.h"
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
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;  // 우클릭 감지

    // UMG 위젯 바인딩
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
    // 좌클릭 기능 (아이템 정보 표시)
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

    // 우클릭 기능 (제작 등 추가 기능)
    void OnRightClickPart(UButton* ClickedButton);

    void UpdateItemInfo(const FString& Name, const FString& Description);

    TMap<UButton*, FString> ButtonPartMap;  //  버튼과 파츠 이름을 매핑
};
