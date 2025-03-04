#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CP_PauseMenu.generated.h"

UCLASS()
class CYBERPUNK_API UCP_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UCP_PauseMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitFromPauseButton;

private:
	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnExitFromPauseButtonClicked();
};