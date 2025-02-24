// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "CP_PlayerController.h"
//#include "GameFramework/CharacterMovementComponent.h"

ACP_Player::ACP_Player()
{
	// camera
	SpringArmLength = 300.f;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = SpringArmLength;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// input
	CharacterInputState.WantsToStrafe = true;
}

void ACP_Player::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float maxaccel = this->GetCharacterMovement()->GetMaxAcceleration();
}

void ACP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ACP_PlayerController* PlayerController = Cast<ACP_PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ACP_Player::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ACP_Player::Look
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ACP_Player::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ACP_Player::StopJump
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ACP_Player::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ACP_Player::StopSprint
				);
			}
		}
	}
}

void ACP_Player::Move(const FInputActionValue& _value)
{
	if (!Controller) return;

	FVector2D MoveInput = _value.Get<FVector2D>();

	/*FRotator rotator = GetControlRotation();
	FVector vector = FVector::ZeroVector;
	vector.Z = rotator.Yaw;
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(vector, MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(vector, MoveInput.Y);
	}*/

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.Y);
	}
}

void ACP_Player::Look(const FInputActionValue& _value)
{
	FVector2D LookInput = _value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ACP_Player::StartCrouch(const FInputActionValue& _value)
{
}

void ACP_Player::StopCrouch(const FInputActionValue& _value)
{
}

void ACP_Player::StartJump(const FInputActionValue& _value)
{
}

void ACP_Player::StopJump(const FInputActionValue& _value)
{
}

void ACP_Player::StartSprint(const FInputActionValue& _value)
{
}

void ACP_Player::StopSprint(const FInputActionValue& _value)
{
}

FCharacterInputState ACP_Player::GetPlayerInputState()
{
	return CharacterInputState;
}

void ACP_Player::SetPlayerInputState(FCharacterInputState _inputState)
{
	CharacterInputState = _inputState;
}
