#include "CP_Ammo.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACP_Ammo::ACP_Ammo()
{
	PrimaryActorTick.bCanEverTick = true;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	RootComponent = AmmoMesh;

	ItemName = FName("Ammo");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoMeshAsset(TEXT("/Game/Gun_BluePrint/ammo/10mmAmmoBox_done_01.10mmAmmoBox_done_01"));
	if (AmmoMeshAsset.Succeeded())
	{
		AmmoMesh->SetStaticMesh(AmmoMeshAsset.Object);
	}


	/*AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AmmoMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	AmmoMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/
}
