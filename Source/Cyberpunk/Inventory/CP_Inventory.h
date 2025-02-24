#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CP_Inventory.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API UCP_Inventory : public UObject
{
    GENERATED_BODY()

public:
    UCP_Inventory();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<TSubclassOf<AActor>> Items;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(TSubclassOf<AActor> NewItem);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(TSubclassOf<AActor> ItemToRemove);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(TSubclassOf<AActor> ItemToCheck) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ClearInventory();
};
