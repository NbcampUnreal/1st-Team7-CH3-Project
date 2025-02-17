// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CP_CharacterBase.h"
#include "CP_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

public:
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float SpringArmLength;
};
