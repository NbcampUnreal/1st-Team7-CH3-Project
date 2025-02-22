#include "Core/CP_AISpawnPoint.h"


ACP_AISpawnPoint::ACP_AISpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Scene);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(Scene);
}


FVector ACP_AISpawnPoint::PortalLocation()
{
	
	return GetActorLocation();
}
