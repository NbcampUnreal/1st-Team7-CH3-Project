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

	UFUNCTION(Exec)
	void AddDeadMenuToViewport();

	void Decrease_AI(); //1씩감소
	void Increase_AI(); //1씩 증가
	void Set_AICount(int32 num);
	int32 Get_AICount();

	void Set_Wave(int32 Wave);
	int32 Get_Wave();

	void Increase_KillCount();
protected:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCP_PlayerHUD> PlayerHUDClass;

	UPROPERTY()
	TObjectPtr<class UCP_PlayerHUD> PlayerHUDInstance;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCP_DeadMenu> DeadMenuClass;

	UPROPERTY()
	TObjectPtr<class UCP_DeadMenu> DeadMenuInstance;

private:
	int32 AI_Counting;
	int32 Wave;
	int32 KillCount;
};
