#include "CP_InventoryWidget.h"

void UCP_InventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // **게임 시작 시 UI를 초기화 (아이템 없음)**
    TArray<FCP_ItemInfo> EmptyItems;
    UpdateInventory(EmptyItems);
}

void UCP_InventoryWidget::UpdateInventory(const TArray<FCP_ItemInfo>& Items)
{
    if (!overlay00 || !overlay01 || !overlay02 || !overlay03 ||
        !overlay10 || !overlay11 || !overlay12 || !overlay13)
    {
        return;
    }

    // 배열로 UI 요소들을 관리하여 코드 간결화
    TArray<UOverlay*> Overlays = { overlay00, overlay01, overlay02, overlay03,
                                   overlay10, overlay11, overlay12, overlay13 };

    TArray<UImage*> Images = { Image_00, Image_01, Image_02, Image_03,
                               Image_10, Image_11, Image_12, Image_13 };

    TArray<UTextBlock*> TextBlocks = { textblock00, textblock01, textblock02, textblock03,
                                       textblock10, textblock11, textblock12, textblock13 };

    // **아이템이 없는 상태에서도 아이템을 먹었을 때와 동일한 UI 유지**
    for (int32 i = 0; i < 8; i++)
    {
        Overlays[i]->SetVisibility(ESlateVisibility::Visible); // 슬롯 유지
        Images[i]->SetBrush(FSlateBrush()); // 빈 슬롯에도 아이템 먹은 후처럼 유지
        Images[i]->SetVisibility(ESlateVisibility::Hidden); // 기본적으로 숨김
        TextBlocks[i]->SetVisibility(ESlateVisibility::Hidden);
        TextBlocks[i]->SetText(FText::FromString(""));
    }

    // **아이템이 있으면 해당 슬롯을 채우기**
    for (int32 i = 0; i < Items.Num() && i < 8; i++)
    {
        const FCP_ItemInfo& Item = Items[i];

        if (Item.ItemIcon)
        {
            // 아이콘 적용
            FSlateBrush Brush;
            Brush.SetResourceObject(Item.ItemIcon);
            Brush.ImageSize = FVector2D(128.0f, 128.0f); // 아이콘 크기 설정
            Images[i]->SetBrush(Brush);
            Images[i]->SetVisibility(ESlateVisibility::Visible);
        }

        if (Item.StackCount > 1)
        {
            TextBlocks[i]->SetText(FText::Format(FText::FromString("x{0}"), Item.StackCount));
            TextBlocks[i]->SetVisibility(ESlateVisibility::Visible);
        }
    }
}
