#include "CP_Heal.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACP_Heal::ACP_Heal()
{
	PrimaryActorTick.bCanEverTick = true;

	HealMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealMesh"));
	RootComponent = HealMesh;

	ItemName = FName("Heal");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HealMeshAsset(TEXT("/Game/Gun_BluePrint/Heal/FirstAidBox.FirstAidBox"));
	if (HealMeshAsset.Succeeded())
	{
		HealMesh->SetStaticMesh(HealMeshAsset.Object);
	}
}
