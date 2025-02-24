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
	int32 RandomChoice = FMath::RandRange(0, 2);

	switch (RandomChoice)
	{
	case 0:
		ItemToSpawn = AmmoClass;
		break;
	case 1:
		ItemToSpawn = GearClass;
		break;
	case 2:
		ItemToSpawn = HealClass;
		break;
	default:
		break;
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
				//  아이템 종류에 따라 크기 자동 조정
				if (ItemToSpawn == AmmoClass)
				{
					MeshComp->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));  // Ammo 크기
				}
				else if (ItemToSpawn == GearClass)
				{
					MeshComp->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));  // Gear 크기
				}
				else if (ItemToSpawn == HealClass)
				{
					MeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));  // Heal 크기
				}
			}
		}
	}
}

void ACP_ItemSpawn::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ACP_Player* Player = Cast<ACP_Player>(OtherActor);
		if (Player && Player->PlayerInventory && SpawnedItem)
		{
			// 플레이어 인벤토리에 아이템 추가
			Player->PickupItem(SpawnedItem->GetClass());

			// 아이템 삭제
			SpawnedItem->Destroy();
			SpawnedItem = nullptr;

			// 아이템 스폰 액터도 제거
			Destroy();
		}
	}
}