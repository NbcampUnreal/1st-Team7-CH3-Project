#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/CP_Inventory.h"
#include "Inventory/CP_InventoryWidget.h"
#include "CP_TestController.generated.h"

UCLASS()
class CYBERPUNK_API ACP_TestController : public APlayerController
{
    GENERATED_BODY()

public:
    ACP_TestController();

protected:
    virtual void BeginPlay() override;

    /** 플레이어의 인벤토리 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    UCP_Inventory* PlayerInventory;

    /** 인벤토리 위젯 클래스 (블루프린트에서 설정) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UCP_InventoryWidget> InventoryWidgetClass;

    /** 실제로 생성된 인벤토리 위젯 */
    UPROPERTY()
    UCP_InventoryWidget* InventoryWidget;
};
