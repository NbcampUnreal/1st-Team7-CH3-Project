// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CP_PotalSpawnPoint.h"

// Sets default values
ACP_PotalSpawnPoint::ACP_PotalSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Scene);
}


FVector ACP_PotalSpawnPoint::PortalLocation()
{

	return GetActorLocation();
}
