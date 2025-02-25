#include "CP_InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"

void UCP_InventoryWidget::UpdateInventoryUI(const TArray<TSubclassOf<AActor>>& Items)
{
    if (!InventoryGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("[InventoryWidget] InventoryGrid is NULL!"));
        return;
    }

    // **기존 슬롯 제거**
    InventoryGrid->ClearChildren();

    UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] Updating Inventory UI with %d items"), Items.Num());

    // **새 슬롯 추가**
    for (int32 i = 0; i < Items.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] Adding slot for item %d"), i);

        UCP_InventorySlot* NewSlot = CreateWidget<UCP_InventorySlot>(this, InventorySlotClass);
        if (NewSlot)
        {
            NewSlot->SetItem(Items[i]->GetName());
            InventoryGrid->AddChildToUniformGrid(NewSlot, i / 4, i % 4);
            UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] Slot added at [%d, %d]"), i / 4, i % 4);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[InventoryWidget] Failed to create InventorySlot!"));
        }
    }
}


void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] NativeConstruct Called"));

    if (!PlayerInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("[InventoryWidget] PlayerInventory is NULL!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] Inventory has %d items"), PlayerInventory->Items.Num());

    UpdateInventoryUI(PlayerInventory->Items);
}

void UCP_InventoryWidget::SetPlayerInventory(UCP_Inventory* NewInventory)
{
    if (!NewInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("[InventoryWidget] SetPlayerInventory FAILED - NewInventory is NULL!"));
        return;
    }

    PlayerInventory = NewInventory;

    UE_LOG(LogTemp, Warning, TEXT("[InventoryWidget] PlayerInventory Set with %d items"), PlayerInventory->Items.Num());

    // **슬롯 업데이트**
    UpdateInventoryUI(PlayerInventory->Items);
}