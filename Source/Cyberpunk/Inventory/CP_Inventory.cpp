#include "CP_Inventory.h"

void UCP_Inventory::AddItem(const FCP_ItemInfo& NewItem)
{
    // 기존 아이템 찾기
    FCP_ItemInfo* ExistingItem = InventoryItems.FindByPredicate([&](const FCP_ItemInfo& Item)
    {
        return Item.ItemName == NewItem.ItemName;
    });

    if (ExistingItem)
    {
        //  같은 아이템이면 개수만 증가
        ExistingItem->StackCount++;
        UE_LOG(LogTemp, Log, TEXT("[Inventory] item : %s | count : %d"), *ExistingItem->ItemName, ExistingItem->StackCount);
    }
    else
    {
        //  새로운 아이템이면 추가
        InventoryItems.Add(NewItem);
        UE_LOG(LogTemp, Log, TEXT("[Inventory] new item: %s"), *NewItem.ItemName);
    }
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
