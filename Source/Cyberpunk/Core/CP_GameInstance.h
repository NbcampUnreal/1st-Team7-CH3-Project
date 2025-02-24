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

	void Decrease_AI();
	void Increase_AI();
	void Set_AICount(int32 num);
	int32 Get_AICount();

	void Set_Wave(int32 Wave);
	int32 Get_Wave();
protected:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCP_PlayerHUD> PlayerHUDClass;

	UPROPERTY()
	TObjectPtr<class UCP_PlayerHUD> PlayerHUDInstance;

private:
	int32 AI_Counting;
	int32 Wave;
};
