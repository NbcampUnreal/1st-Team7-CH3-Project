// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GunPart.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGunPart : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERPUNK_API IGunPart
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Initialize(const FString& MeshName) = 0;
	virtual USkeletalMeshComponent* GetMesh() const = 0;
};
