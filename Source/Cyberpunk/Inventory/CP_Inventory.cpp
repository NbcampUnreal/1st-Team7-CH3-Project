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
    
    if (!Owner) return;

    ACP_Player* Player = Cast<ACP_Player>(Owner);
    ACP_Guns* Gun = Cast<ACP_Guns>(Owner);

    if (ItemInfo.ItemType == ECP_ItemType::Heal)
    {
        /* 플레이어 체력 증가 기믹 차후 구현 
        if (Player)
        {
            int32 HealAmount = 50;  // 체력 회복량 (예제)
            Player->IncreaseHealth(HealAmount);  // 플레이어 체력 증가
            UE_LOG(LogTemp, Log, TEXT("[UCP_Inventory] Used Heal Item. +%d HP"), HealAmount);
        }*/
        
    }
    else if (ItemInfo.ItemType == ECP_ItemType::Ammo)
    {
        if (Gun)
        {
            Gun->Reload();  //  총기 재장전 실행
        }
    }
    RemoveItem(ItemInfo);
    
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
