// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CP_PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// Anim Graph
	UFUNCTION(BlueprintCallable)
	void OnStateEntry_TransitionToIdleLoop();

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Test")
	int32 TestInt;
};
