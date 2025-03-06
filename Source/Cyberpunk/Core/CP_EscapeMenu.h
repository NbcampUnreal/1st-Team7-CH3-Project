#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CP_EscapeMenu.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_EscapeMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

protected:

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Resume_Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Exit_Button;
	
};
