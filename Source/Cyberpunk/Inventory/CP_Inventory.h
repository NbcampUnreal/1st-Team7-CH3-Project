#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CP_ItemInfo.h"
#include "Guns/CP_TriggerInfo.h"
#include "CP_Inventory.generated.h"

class ACP_Guns;
class ACP_Player;

UCLASS(Blueprintable, BlueprintType)
class CYBERPUNK_API UCP_Inventory : public UObject
{
    GENERATED_BODY()

public:

    void AddItem(const FCP_ItemInfo& NewItem);
    void UseItem(const FCP_ItemInfo& ItemInfo);
    void Initialize(AActor* InOwner);
    void ReduceItemCount(const FCP_ItemInfo&  ItemInfo);
    bool HasItem(const FString& ItemName) const;
    TArray<FCP_ItemInfo> GetInventoryItems() const;

private:
    // 아이템 목록
    UPROPERTY()
    TArray<FCP_ItemInfo> InventoryItems;

    UPROPERTY()
    AActor* Owner;
};
