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

    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitFromPauseButton;

    UPROPERTY()
    UUserWidget* PauseMenuWidget; // Pause 메뉴 위젯

private:
    UFUNCTION()
    void OnStartButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();

    // 게임 재개 또는 종료를 위한 메뉴 표시 함수
    UFUNCTION()
    void ShowPauseMenu();

    // 게임 재개 함수
    UFUNCTION()
    void OnResumeButtonClicked();

    // 게임 종료 함수
    UFUNCTION()
    void OnExitFromPauseButtonClicked();
};
