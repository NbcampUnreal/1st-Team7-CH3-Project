#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "CP_ItemInfo.generated.h"

/** 아이템 타입을 구분하는 열거형 */
UENUM(BlueprintType)
enum class ECP_ItemType : uint8
{
    Gear UMETA(DisplayName = "Gear"),
    Heal UMETA(DisplayName = "Heal"),
    Ammo UMETA(DisplayName = "Ammo"),
    GunPart UMETA(DisplayName = "GunPart")
};

/** 인벤토리에 저장될 아이템 정보 */
USTRUCT(BlueprintType)
struct FCP_ItemInfo
{
    GENERATED_BODY()

public:
    /** 아이템의 타입 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    ECP_ItemType ItemType;

    /** 아이템 이름 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString ItemName;

    /** 아이템 아이콘 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* ItemIcon;

    /** 기본 생성자 */
    FCP_ItemInfo()
        : ItemType(ECP_ItemType::Gear), ItemName(TEXT("")), ItemIcon(nullptr) {}
};
