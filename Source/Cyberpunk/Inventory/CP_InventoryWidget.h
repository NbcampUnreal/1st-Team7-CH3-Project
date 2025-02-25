#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CP_InventorySlot.h"
#include "CP_Inventory.h" 
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "CP_InventoryWidget.generated.h"

UCLASS()
class CYBERPUNK_API UCP_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** 인벤토리 UI를 업데이트하는 함수 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UpdateInventoryUI(const TArray<TSubclassOf<AActor>>& Items);
    virtual void NativeConstruct() override;

    /** 플레이어 인벤토리 설정 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetPlayerInventory(UCP_Inventory* NewInventory);
protected:
    /** 기어 스탯 표시 */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* GearStats;

    /** 인벤토리 슬롯 (8칸) */
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<UCP_InventorySlot> InventorySlotClass;

    /** 플레이어 인벤토리 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    UCP_Inventory* PlayerInventory;


};
