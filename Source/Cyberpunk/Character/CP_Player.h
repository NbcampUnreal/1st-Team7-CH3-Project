// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"
#include "CP_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

USTRUCT(BlueprintType)
struct FCharacterInputState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool WantsToSprint;

	UPROPERTY(BlueprintReadWrite)
	bool WantsToWalk;

	UPROPERTY(BlueprintReadWrite)
	bool WantsToStrafe;

	UPROPERTY(BlueprintReadWrite)
	bool WantsToAim;
};

UCLASS()
class CYBERPUNK_API ACP_Player : public ACP_CharacterBase
{
	GENERATED_BODY()
public:

	ACP_Player();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement Function
public:
	UFUNCTION()
	void Move(const FInputActionValue& _value);

	UFUNCTION()
	void Look(const FInputActionValue& _value);

	UFUNCTION()
	void StartCrouch(const FInputActionValue& _value);

	UFUNCTION()
	void StopCrouch(const FInputActionValue& _value);

	UFUNCTION()
	void StartJump(const FInputActionValue& _value);

	UFUNCTION()
	void StopJump(const FInputActionValue& _value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& _value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& _value);

	UFUNCTION()
	FCharacterInputState GetPlayerInputState();

	UFUNCTION()
	void SetPlayerInputState(FCharacterInputState _inputState);

public:
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SpringArmLength;

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FCharacterInputState CharacterInputState;
};
