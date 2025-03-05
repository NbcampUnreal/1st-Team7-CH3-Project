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

    ACP_Player* Player = Cast<ACP_Player>(Owner);
    if (!Player)
    {
        return;
    }

    ACP_Guns* EquippedGun = Player->EquippedGun;
    if (!EquippedGun)
    {
        return;
    }

    if (ItemInfo.ItemType == ECP_ItemType::Ammo)
    {
        if (EquippedGun->TriggerInfo)
        {
            int32 MagazineCapacity = EquippedGun->TriggerInfo->MagazineCapacity;
            if (MagazineCapacity > 0)
            {
                EquippedGun->MaxAmmo += MagazineCapacity;
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] MaxAmmo increased by %d, New MaxAmmo: %d"),
                    MagazineCapacity, EquippedGun->MaxAmmo);
            }
        }

    }
}



void UCP_Inventory::UseItem(const FCP_ItemInfo& ItemInfo)
{
    if (!Owner)
    {
        return;
    }

    ACP_Player* Player = Cast<ACP_Player>(Owner);
    ACP_Guns* Gun = nullptr;

    if (Player)
    {
        Gun = Player->EquippedGun;
    }

    if (Gun)
    {
        Gun->Reload();
    }

    UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Attempting to use item: %s"), *ItemInfo.ItemName);

    if (ItemInfo.ItemType == ECP_ItemType::Heal)
    {
        if (Player)
        {
            int HealAmount = 50; 
            UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Heal item used. Healing for: %d"), HealAmount);
            Player->Heal(HealAmount);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[UCP_Inventory] ERROR: Player is nullptr! Cannot heal."));
        }
    }

    else if (ItemInfo.ItemType == ECP_ItemType::Ammo)
    {
        return;
    }

    else if (ItemInfo.ItemType == ECP_ItemType::Gear)
    {
        return;
    }

    ReduceItemCount(ItemInfo);

    if (Player)
    {
        if (Player->InventoryWidget)
        {
            Player->InventoryWidget->UpdateInventory(GetInventoryItems());
        }

    }
}




void UCP_Inventory::ReduceItemCount(const FCP_ItemInfo& ItemInfo)
{
    for (int32 i = 0; i < InventoryItems.Num(); i++)
    {
        if (InventoryItems[i].ItemName == ItemInfo.ItemName)
        {
            if (InventoryItems[i].StackCount > 1)
            {
                InventoryItems[i].StackCount--;
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Reduced stack count of %s, Remaining: %d"),
                    *InventoryItems[i].ItemName, InventoryItems[i].StackCount);
            }
            else
            {
                InventoryItems.RemoveAt(i);  //  바로 삭제
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Removed item: %s"), *ItemInfo.ItemName);
            }
            break; //  한 번만 실행 후 루프 종료
        }
    }

    // UI 업데이트
    if (Owner)
    {
        ACP_Player* Player = Cast<ACP_Player>(Owner);
        if (Player && Player->InventoryWidget)
        {
            Player->InventoryWidget->UpdateInventory(GetInventoryItems());
        }
    }
}









int32 UCP_Inventory::GetItemCount(const FString& ItemName) const
{
    int32 TotalCount = 0;

    for (const FCP_ItemInfo& Item : InventoryItems)
    {
        if (Item.ItemName == ItemName)
        {
            TotalCount += Item.StackCount;  // 스택된 아이템 개수 합산
        }
    }

    return TotalCount;
}



void UCP_Inventory::ReduceItemCountByName(const FString& ItemName, int32 ReduceAmount)
{
    for (int32 i = 0; i < InventoryItems.Num(); i++)
    {
        if (InventoryItems[i].ItemName == ItemName)
        {
            if (InventoryItems[i].StackCount > ReduceAmount)
            {
                InventoryItems[i].StackCount -= ReduceAmount;
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Reduced %d from %s, Remaining: %d"),
                    ReduceAmount, *ItemName, InventoryItems[i].StackCount);
            }
            else
            {
                ReduceAmount -= InventoryItems[i].StackCount;
                UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Removed all %s, Moving to next slot"), *ItemName);
                InventoryItems.RemoveAt(i);
                i--; // RemoveAt() 하면 Index가 줄어드니까 보정

                if (ReduceAmount <= 0)
                    break;
            }
        }
    }

    //  UI 업데이트
    if (Owner)
    {
        ACP_Player* Player = Cast<ACP_Player>(Owner);
        if (Player && Player->InventoryWidget)
        {
            Player->InventoryWidget->UpdateInventory(GetInventoryItems());
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
