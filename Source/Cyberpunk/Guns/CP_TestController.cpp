#include "CP_TestController.h"
#include "Inventory/CP_Inventory.h"
#include "CP_BarrelInfo.h"
#include "Blueprint/UserWidget.h"

ACP_TestController::ACP_TestController()
{
    // 인벤토리 생성
    PlayerInventory = CreateDefaultSubobject<UCP_Inventory>(TEXT("PlayerInventory"));
}

void ACP_TestController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[TestController] BeginPlay Called"));

    if (!PlayerInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("[TestController] PlayerInventory is NULL in Controller!"));
        return;
    }

    // **기본 아이템 추가 (디버깅용)**
    PlayerInventory->AddItem(ACP_BarrelInfo::StaticClass());

    UE_LOG(LogTemp, Warning, TEXT("[TestController] PlayerInventory Initialized with %d items"), PlayerInventory->Items.Num());

    // **UI 생성**
    if (InventoryWidgetClass)
    {
        InventoryWidget = CreateWidget<UCP_InventoryWidget>(this, InventoryWidgetClass);
        if (InventoryWidget)
        {
            InventoryWidget->AddToViewport();

            // **여기서 인벤토리를 위젯에 설정!**
            InventoryWidget->SetPlayerInventory(PlayerInventory);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[TestController] Failed to create InventoryWidget!"));
        }
    }
}
