#include "CP_InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!InventoryGrid) return;

    // 기존 UI 삭제
    InventoryGrid->ClearChildren();

    int32 SlotIndex = 0;
    for (const FCP_ItemInfo& Item : Items)
    {
        // UI에서 새로운 버튼을 동적으로 생성
        UButton* ItemButton = NewObject<UButton>(this);
        UImage* ItemIcon = NewObject<UImage>(this);
        UTextBlock* ItemName = NewObject<UTextBlock>(this);

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
}
