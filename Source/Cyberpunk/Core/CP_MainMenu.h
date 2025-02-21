#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CP_MainMenu.generated.h"

UCLASS()
class CYBERPUNK_API UCP_MainMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UCP_MainMenu(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

private:
    UFUNCTION()
    void OnStartButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();

    // ���� �簳 �Ǵ� ���Ḧ ���� �޴� ǥ�� �Լ�
    UFUNCTION()
    void ShowPauseMenu();

    // ���� �簳 �Լ�
    UFUNCTION()
    void OnResumeButtonClicked();

    // ���� ���� �Լ�
    UFUNCTION()
    void OnExitFromPauseButtonClicked();

    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitFromPauseButton;

    UPROPERTY()
    UUserWidget* PauseMenuWidget; // Pause �޴� ����
};
