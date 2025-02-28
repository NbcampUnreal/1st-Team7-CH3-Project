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
    }
    else
    {
        //  새로운 아이템이면 추가
        InventoryItems.Add(NewItem);
    }
}


void UCP_Inventory::RemoveItem(const FCP_ItemInfo& ItemInfo)
{
    if (InventoryItems.Contains(ItemInfo))
    {
        InventoryItems.Remove(ItemInfo);
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
