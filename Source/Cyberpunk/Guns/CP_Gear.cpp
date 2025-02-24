#include "CP_Gear.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACP_Gear::ACP_Gear()
{
	PrimaryActorTick.bCanEverTick = true;

	GearMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GearMesh"));

	RootComponent = GearMesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GearMeshAsset(TEXT("/Game/Gun_BluePrint/Gear/Gear1.Gear1"));
	if (GearMeshAsset.Succeeded())
	{
		GearMesh->SetSkeletalMesh(GearMeshAsset.Object);
	}
}
