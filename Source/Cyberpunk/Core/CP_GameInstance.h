// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CP_GameInstance.generated.h"


UCLASS()
class CYBERPUNK_API UCP_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	UCP_GameInstance();

protected:

	virtual void Init() override;

public:

	class UCP_PlayerHUD* GetPlayerHUD();

	UFUNCTION(Exec)
	void AddPlayerHUDToViewport();
	UFUNCTION(Exec)
	void RemovePlayerHUDToViewport();

protected:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCP_PlayerHUD> PlayerHUDClass;

	UPROPERTY()
	TObjectPtr<class UCP_PlayerHUD> PlayerHUDInstance;


	int32 AI_Counting;

};
