// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CP_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// chaching Owner Character
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ACharacter* OwnerCharacter;

	virtual void NativeInitializeAnimation() override;
};
