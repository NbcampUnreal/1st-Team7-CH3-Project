// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CP_AnimInstance.h"
#include "CP_PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_PlayerAnimInstance : public UCP_AnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
};
