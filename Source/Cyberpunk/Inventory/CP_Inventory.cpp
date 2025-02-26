#include "CP_Inventory.h"

void UCP_Inventory::AddItem(const FCP_ItemInfo& NewItem)
{
    InventoryItems.Add(NewItem);
    UE_LOG(LogTemp, Log, TEXT("Item obtained : %s"), *NewItem.ItemName);
}

void UCP_Inventory::RemoveItem(const FString& ItemName)
{
    int32 Index = InventoryItems.IndexOfByPredicate([&](const FCP_ItemInfo& Item) {
        return Item.ItemName == ItemName;
    });

    if (Index != INDEX_NONE)
    {
        InventoryItems.RemoveAt(Index);
        UE_LOG(LogTemp, Log, TEXT("Item erased : %s"), *ItemName);
    }
}

bool UCP_Inventory::HasItem(const FString& ItemName) const
{
    return InventoryItems.ContainsByPredicate([&](const FCP_ItemInfo& Item) {
        return Item.ItemName == ItemName;
    });
}

TArray<FCP_ItemInfo> UCP_Inventory::GetInventoryItems() const
{
    return InventoryItems;
}
