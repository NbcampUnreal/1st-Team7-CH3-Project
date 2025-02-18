// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACP_Player::ACP_Player()
{
	SpringArmLength = 300.f;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = SpringArmLength;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;


}

void ACP_Player::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
