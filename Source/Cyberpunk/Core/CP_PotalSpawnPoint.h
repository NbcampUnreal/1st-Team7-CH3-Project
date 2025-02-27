// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_PotalSpawnPoint.generated.h"

UCLASS()
class CYBERPUNK_API ACP_PotalSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACP_PotalSpawnPoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	FVector PortalLocation();

};