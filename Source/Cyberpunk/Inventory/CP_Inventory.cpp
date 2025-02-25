#include "CP_Inventory.h"
#include "Guns/CP_BodyInfo.h"
UCP_Inventory::UCP_Inventory()
{
    Items.Empty();

    static ConstructorHelpers::FClassFinder<ACP_BodyInfo> DefaultBody(TEXT("Blueprint'/Game/Gun_BluePrint/BP_BodyFire.BP_BodyFire_C'"));
    if (DefaultBody.Succeeded())
    {
        Items.Add(DefaultBody.Class);
    }
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

