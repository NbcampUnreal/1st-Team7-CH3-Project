#include "CP_InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Guns/CP_Guns.h"
#include "Guns/CP_BarrelInfo.h"
#include "Guns/CP_BodyInfo.h"
#include "Guns/CP_TriggerInfo.h"

void UCP_InventorySlot::SetItem(const FString& NewItemName)
{
    ItemName = NewItemName;

    // UI에 아이템 이름 표시
    if (ItemNameText)
    {
        ItemNameText->SetText(FText::FromString(NewItemName));
    }

    // 아이콘 찾기
    UTexture2D* IconTexture = nullptr;

    /** 배럴 클래스 검사 */
    for (TObjectIterator<UClass> It; It; ++It)
    {
        if (It->IsChildOf(ACP_BarrelInfo::StaticClass()))
        {
            ACP_BarrelInfo* DefaultBarrel = Cast<ACP_BarrelInfo>(It->GetDefaultObject());
            if (DefaultBarrel && DefaultBarrel->PartName == NewItemName)
            {
                IconTexture = DefaultBarrel->IconTexture;
                break;
            }
        }
    }

    /** 바디 클래스 검사 */
    if (!IconTexture)
    {
        for (TObjectIterator<UClass> It; It; ++It)
        {
            if (It->IsChildOf(ACP_BodyInfo::StaticClass()))
            {
                ACP_BodyInfo* DefaultBody = Cast<ACP_BodyInfo>(It->GetDefaultObject());
                if (DefaultBody && DefaultBody->PartName == NewItemName)
                {
                    IconTexture = DefaultBody->IconTexture;
                    break;
                }
            }
        }
    }

    /** 트리거 클래스 검사 */
    if (!IconTexture)
    {
        for (TObjectIterator<UClass> It; It; ++It)
        {
            if (It->IsChildOf(ACP_TriggerInfo::StaticClass()))
            {
                ACP_TriggerInfo* DefaultTrigger = Cast<ACP_TriggerInfo>(It->GetDefaultObject());
                if (DefaultTrigger && DefaultTrigger->PartName == NewItemName)
                {
                    IconTexture = DefaultTrigger->IconTexture;
                    break;
                }
            }
        }
    }

    /**아이콘 설정 */
    if (IconTexture && ItemIcon)
    {
        ItemIcon->SetBrushFromTexture(IconTexture);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Icon not found for: %s"), *NewItemName);
    }
}
