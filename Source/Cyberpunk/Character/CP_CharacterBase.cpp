// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CP_CharacterBase.h"

// Sets default values
ACP_CharacterBase::ACP_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACP_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACP_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACP_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

