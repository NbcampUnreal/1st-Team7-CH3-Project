// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CP_PlayerAnimInstance.h"
#include "CP_Player.h"

void UCP_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACP_Player>(TryGetPawnOwner());
}
