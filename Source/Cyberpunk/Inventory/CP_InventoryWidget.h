#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CP_ItemInfo.h"
#include "CP_InventoryWidget.generated.h"

class UUniformGridPanel;
class UButton;

UCLASS()
class CYBERPUNK_API UCP_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** 인벤토리 UI를 업데이트 */
    void UpdateInventory(const TArray<FCP_ItemInfo>& Items);

protected:
    virtual void NativeConstruct() override;

private:
    /** 인벤토리 슬롯을 배치할 패널 */
    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGrid;

};
