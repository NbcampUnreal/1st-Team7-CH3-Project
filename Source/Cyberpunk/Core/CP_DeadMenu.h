#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CP_DeadMenu.generated.h"

/**
 * 
 */
UCLASS()
class CYBERPUNK_API UCP_DeadMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

protected:

	UFUNCTION()
	void OnExitButtonClicked();

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Exit_Button;
	
};
