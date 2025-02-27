
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "CP_ItemInfo.h"
#include "Components/Overlay.h"
#include "CP_InventoryWidget.generated.h"

class UUniformGridPanel;
class UButton;

UCLASS()
class CYBERPUNK_API UCP_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
   // virtual void NativeConstruct() override;

public:
    // WBP에서 만든 8개의 슬롯 UI 요소 바인딩
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay00;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay01;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay02;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay03;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay10;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay11;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay12;
    UPROPERTY(meta = (BindWidget))
    UOverlay* overlay13;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_00;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_01;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_02;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_03;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_10;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_11;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_12;
    UPROPERTY(meta = (BindWidget))
    UButton* Button_13;

    UPROPERTY(meta = (BindWidget))
    UImage* Image_00;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_01;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_02;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_03;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_10;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_11;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_12;
    UPROPERTY(meta = (BindWidget))
    UImage* Image_13;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock00;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock01;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock02;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock03;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock10;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock11;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock12;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* textblock13;

    // 인벤토리 업데이트 함수
    void UpdateInventory(const TArray<FCP_ItemInfo>& Items);
};
