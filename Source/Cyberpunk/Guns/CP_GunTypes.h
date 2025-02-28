#pragma once

#include "CoreMinimal.h"
#include "CP_GunTypes.generated.h"

UENUM(BlueprintType)
enum class EGunPartType : uint8
{
    Barrel UMETA(DisplayName = "Barrel"),
    Body UMETA(DisplayName = "Body"),
    Trigger UMETA(DisplayName = "Trigger")
};
