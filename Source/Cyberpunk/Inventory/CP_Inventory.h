#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CP_ItemInfo.h"
#include "CP_Inventory.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CYBERPUNK_API UCP_Inventory : public UObject
{
    GENERATED_BODY()

public:
    //아이템 추가 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(const FCP_ItemInfo& NewItem);

    // 아이템 제거 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(const FCP_ItemInfo& ItemInfo);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(const FString& ItemName) const;

    // 현재 인벤토리 아이템 리스트 반환 
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<FCP_ItemInfo> GetInventoryItems() const;

private:
    // 아이템 목록
    UPROPERTY()
    TArray<FCP_ItemInfo> InventoryItems;
};
