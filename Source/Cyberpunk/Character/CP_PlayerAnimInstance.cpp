// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CP_PlayerAnimInstance.h"

void UCP_PlayerAnimInstance::OnStateEntry_TransitionToIdleLoop()
{
	UE_LOG(LogTemp, Warning, TEXT("TESTSETSET"));
}

void UCP_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}
