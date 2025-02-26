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
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName; // 아이템 이름

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECP_ItemType ItemType; // 아이템 타입

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* ItemIcon; // 아이템 아이콘

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StackCount = 1; //  아이템 개수 추가 (기본값 1)
};