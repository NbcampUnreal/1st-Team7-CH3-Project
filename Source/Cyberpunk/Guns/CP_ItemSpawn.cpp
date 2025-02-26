#include "CP_ItemSpawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACP_ItemSpawn::ACP_ItemSpawn()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootScene);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACP_ItemSpawn::OnItemOverlap);
    CollisionComponent->SetSphereRadius(50.0f);

    //  코드에서 AmmoClass, GearClass, HealClass 로드
    static ConstructorHelpers::FClassFinder<AActor> AmmoBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BPCP_Ammo.BPCP_Ammo_C'"));
    if (AmmoBPClass.Succeeded())
    {
        AmmoClass = AmmoBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<AActor> GearBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BPCP_Gear.BPCP_Gear_C'"));
    if (GearBPClass.Succeeded())
    {
        GearClass = GearBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<AActor> HealBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BPCP_Heal.BPCP_Heal_C'"));
    if (HealBPClass.Succeeded())
    {
        HealClass = HealBPClass.Class;
    }

    // 초기 값 설정
    TimeElapsed = 0.0f;
}

void ACP_ItemSpawn::BeginPlay()
{
    Super::BeginPlay();
    SpawnItem();
}

void ACP_ItemSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;

    if (SpawnedItem)
    {
        //   위아래 움직임 (0.0 ~ 10.0 유닛 오차)
        FVector NewLocation = InitialSpawnLocation;
        NewLocation.Z += FMath::Cos(TimeElapsed * 2.0f) * 10.0f; // 부드러운 움직임

        SpawnedItem->SetActorLocation(NewLocation);
    }
}

void ACP_ItemSpawn::SpawnItem()
{
    if (SpawnedItem)
    {
        SpawnedItem->Destroy();
        SpawnedItem = nullptr;
    }

    //  랜덤 아이템 선택 (Ammo, Gear, Heal)
    TSubclassOf<AActor> ItemToSpawn = nullptr;
    ECP_ItemType ItemType;
    FString ItemName;
    UTexture2D* ItemIcon = nullptr;

    int32 RandomChoice = FMath::RandRange(0, 2);
    switch (RandomChoice)
    {
    case 0:
        ItemToSpawn = AmmoClass;
        ItemType = ECP_ItemType::Ammo;
        ItemName = TEXT("Ammo Pack");
        ItemIcon = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Gun_BluePrint/RenderTargets/RT_Ammo.RT_Ammo"));
        break;
    case 1:
        ItemToSpawn = GearClass;
        ItemType = ECP_ItemType::Gear;
        ItemName = TEXT("Gear");
        ItemIcon = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Gun_BluePrint/RenderTargets/RT_Gear"));
        break;
    case 2:
        ItemToSpawn = HealClass;
        ItemType = ECP_ItemType::Heal;
        ItemName = TEXT("Heal Pack");
        ItemIcon = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Gun_BluePrint/RenderTargets/RT_Heal.RT_Heal"));
        break;
    default:
        return;
    }

    if (ItemToSpawn)
    {
        InitialSpawnLocation = GetActorLocation();
        FRotator SpawnRotation = FRotator::ZeroRotator;
        SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemToSpawn, InitialSpawnLocation, SpawnRotation);

        if (SpawnedItem)
        {
            UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(SpawnedItem->GetRootComponent());
            if (MeshComp)
            {
                if (ItemToSpawn == AmmoClass)
                {
                    MeshComp->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
                }
                else if (ItemToSpawn == GearClass)
                {
                    MeshComp->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
                }
                else if (ItemToSpawn == HealClass)
                {
                    MeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
                }
            }
        }

        // 스폰된 아이템의 정보를 저장
        SpawnedItemInfo.ItemType = ItemType;
        SpawnedItemInfo.ItemName = ItemName;
        SpawnedItemInfo.ItemIcon = ItemIcon;
    }
}


void ACP_ItemSpawn::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("[ItemSpawn] OnItemOverlap excuted"));

    if (OtherActor)
    {
        ACP_Player* Player = Cast<ACP_Player>(OtherActor);
        if (Player && Player->PlayerInventory)
        {
            UE_LOG(LogTemp, Log, TEXT("[ItemSpawn] item obtained: %s | type: %d"),
                *SpawnedItemInfo.ItemName, static_cast<int32>(SpawnedItemInfo.ItemType));

            Player->PickupItem(SpawnedItemInfo.ItemType, SpawnedItemInfo.ItemName, SpawnedItemInfo.ItemIcon);

            if (SpawnedItem)
            {
                SpawnedItem->Destroy();
                SpawnedItem = nullptr;
            }

            Destroy();
        }
    }
}
