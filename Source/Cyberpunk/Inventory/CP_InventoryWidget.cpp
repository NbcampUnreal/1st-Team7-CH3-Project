#include "CP_InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

}

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!InventoryGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("[UpdateInventory] InventoryGrid nullptr!"));
        return;
    }

    // 기존 UI 슬롯 삭제
    InventoryGrid->ClearChildren();

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] updated started: %d"), Items.Num());

    int32 SlotIndex = 0;
    for (const FCP_ItemInfo& Item : Items)
    {
        UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] slot added: %s"), *Item.ItemName);

        // UI에서 새로운 버튼을 동적으로 생성
        UButton* ItemButton = NewObject<UButton>(this);
        UImage* ItemIcon = NewObject<UImage>(this);
        UTextBlock* ItemName = NewObject<UTextBlock>(this);


        FSlateBrush Brush;
        Brush.SetResourceObject(Item.ItemIcon);
        Brush.ImageSize = FVector2D(64.0f, 64.0f); // 아이콘 크기 키우기

        ItemIcon->SetBrush(Brush);

        //  버튼 크기 조정 (슬롯 크기 조절 가능)
        ItemButton->SetRenderTransform(FWidgetTransform(FVector2D(0, 0), FVector2D(1.5f, 1.5f), FVector2D(0, 0), 0.0f));

        // 아이콘 설정
        if (Item.ItemIcon)
        {
            ItemIcon->SetBrushFromTexture(Item.ItemIcon);
        }

        // 아이템 이름 설정
        ItemName->SetText(FText::FromString(Item.ItemName));

        // 버튼에 아이콘 추가
        ItemButton->AddChild(ItemIcon);

        // 슬롯 패널에 버튼 추가
        InventoryGrid->AddChildToUniformGrid(ItemButton, SlotIndex / 4, SlotIndex % 4);

        SlotIndex++;
        if (SlotIndex >= 8) break; // 8칸까지만 허용
    }

    UE_LOG(LogTemp, Log, TEXT("[UpdateInventory] Inventory updated!"));
}


