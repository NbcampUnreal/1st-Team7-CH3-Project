#include "CP_ItemSpawn.h"
#include "Engine/World.h"

ACP_ItemSpawn::ACP_ItemSpawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootScene);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACP_ItemSpawn::OnItemOverlap);
}

void ACP_ItemSpawn::BeginPlay()
{
	Super::BeginPlay();
	SpawnItem();
}

void ACP_ItemSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACP_ItemSpawn::SpawnItem()
{
	if (SpawnedItem)
	{
		SpawnedItem->Destroy();
	}

	TSubclassOf<AActor> ItemToSpawn = UKismetMathLibrary::RandomBool() ? AmmoClass : GearClass;

	if (ItemToSpawn)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);

		if (SpawnedItem)
		{
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(SpawnedItem->GetRootComponent());
			if (MeshComp)
			{
				if (ItemToSpawn == AmmoClass)
				{
					MeshComp->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));  // Ammo 크기 설정
				}
				else if (ItemToSpawn == GearClass)
				{
					MeshComp->SetWorldScale3D(FVector(4.0f, 4.0f, 4.0f));  // Gear 크기 설정
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
		if (SpawnedItem)
		{
			SpawnedItem->Destroy();
			SpawnedItem = nullptr;
		}
		Destroy();
	}
}

