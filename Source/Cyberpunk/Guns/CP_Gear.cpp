#include "CP_Gear.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACP_Gear::ACP_Gear()
{
	PrimaryActorTick.bCanEverTick = true;

	GearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GearMesh"));
	RootComponent = GearMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GearMeshAsset(TEXT("/Game/Gun_BluePrint/Gear/Gear_StaticMesh.Gear_StaticMesh"));
	if (GearMeshAsset.Succeeded())
	{
		GearMesh->SetStaticMesh(GearMeshAsset.Object);
	}
}
