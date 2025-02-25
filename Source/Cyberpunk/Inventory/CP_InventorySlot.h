#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CP_InventorySlot.generated.h"

UCLASS()
class CYBERPUNK_API UCP_InventorySlot : public UUserWidget
{
    GENERATED_BODY()

public:
    /** 슬롯에 아이템 설정 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetItem(const FString& ItemName);

protected:
    /** 아이템 아이콘 */
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemIcon;

    /** 아이템 이름 */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemNameText;

    /** 슬롯이 저장할 아이템 이름 */
    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    FString ItemName;

    /** 우클릭 이벤트 처리 */
    //virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
