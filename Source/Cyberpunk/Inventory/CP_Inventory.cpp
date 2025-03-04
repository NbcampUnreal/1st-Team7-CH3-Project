#include "CP_Inventory.h"
#include "Guns/CP_Guns.h"
#include "Character/CP_Player.h"

void UCP_Inventory::Initialize(AActor* InOwner)
{
    Owner = InOwner; 
}

void UCP_Inventory::AddItem(const FCP_ItemInfo& ItemInfo)
{
    InventoryItems.Add(ItemInfo);
    UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Added item: %s"), *ItemInfo.ItemName);

    if (!Owner) return;

    if (ItemInfo.ItemType == ECP_ItemType::Ammo)
    {
        ACP_Guns* EquippedGun = Cast<ACP_Guns>(Owner);

        if (EquippedGun && EquippedGun->TriggerInfo)
        {
            int32 MagazineCapacity = EquippedGun->TriggerInfo->MagazineCapacity;

            EquippedGun->MaxAmmo += MagazineCapacity;
            UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] MaxAmmo increased by %d, New MaxAmmo: %d"), MagazineCapacity, EquippedGun->MaxAmmo);
        }
    }
}

void UCP_Inventory::UseItem(const FCP_ItemInfo& ItemInfo)
{
    if (!Owner)  return;

    ACP_Player* Player = Cast<ACP_Player>(Owner);
    ACP_Guns* Gun = Cast<ACP_Guns>(Owner);

    if (ItemInfo.ItemType == ECP_ItemType::Heal)
    {
        /*
        Heal 아이템 사용 
        */
    }

    else if (ItemInfo.ItemType == ECP_ItemType::Ammo)
    {
        if (Gun)
        {
            Gun->Reload();
        }
    }

    else if (ItemInfo.ItemType == ECP_ItemType::Gear)
    {
        /*
        Gear 아이템 사용
        */
    }

    ReduceItemCount(ItemInfo);

    if (Player)
    {
        if (Player->InventoryWidget)
        {
            Player->InventoryWidget->UpdateInventory(GetInventoryItems());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[UCP_Inventory] ERROR: InventoryWidget is nullptr!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[UCP_Inventory] ERROR: Player is nullptr!"));
    }
}


void UCP_Inventory::ReduceItemCount(const FCP_ItemInfo& ItemInfo)
{
    for (int32 i = 0; i < InventoryItems.Num(); i++)
    {
        if (InventoryItems[i].ItemName == ItemInfo.ItemName)
        {
            // 스택이 여러 개일 경우 개수 감소
            if (InventoryItems[i].StackCount > 1)
            {
                InventoryItems[i].StackCount--;
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Reduced stack count of %s, Remaining: %d"),
                    *InventoryItems[i].ItemName, InventoryItems[i].StackCount);
            }
            else
            {
                // 스택이 1개라면 아이템 삭제
                InventoryItems.RemoveAt(i);
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Removed item: %s"), *ItemInfo.ItemName);
            }
            break;
        }
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
