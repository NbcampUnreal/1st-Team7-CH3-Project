#include "CP_Inventory.h"

UCP_Inventory::UCP_Inventory()
{
    Items.Empty();
}

void UCP_Inventory::AddItem(TSubclassOf<AActor> NewItem)
{
    if (NewItem)
    {
        Items.Add(NewItem);
    }
}

void UCP_Inventory::RemoveItem(TSubclassOf<AActor> ItemToRemove)
{
    if (Items.Contains(ItemToRemove))
    {
        Items.Remove(ItemToRemove);
    }
}

bool UCP_Inventory::HasItem(TSubclassOf<AActor> ItemToCheck) const
{
    return Items.Contains(ItemToCheck);
}

void UCP_Inventory::ClearInventory()
{
    Items.Empty();
}
