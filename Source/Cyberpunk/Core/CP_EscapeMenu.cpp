#include "Core/CP_EscapeMenu.h"

#include "Cyberpunk.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_GameInstance.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UCP_EscapeMenu::NativeConstruct()
{
	if (Resume_Button)
	{
		Resume_Button->OnClicked.AddDynamic(this, &UCP_EscapeMenu::OnResumeButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCP_EscapeMenu: Resume_Button 위젯이 바인딩되지 않았습니다."));
	}

	if (Exit_Button)
	{
		Exit_Button->OnClicked.AddDynamic(this, &UCP_EscapeMenu::OnExitButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCP_EscapeMenu: Exit_Button 위젯이 바인딩되지 않았습니다."));
	}
}

void UCP_EscapeMenu::OnResumeButtonClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr)
	{
		CP_LOG(Warning, TEXT("PlayerController == nullptr"));
		return;
	}

	UCP_GameInstance* Instance = Cast<UCP_GameInstance>(PlayerController->GetGameInstance());
	if (Instance == nullptr)
	{
		CP_LOG(Warning, TEXT("Instance == nullptr"));
		return;
	}

	Instance->RemoveEscapeMenuToViewport();
	PlayerController->SetPause(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

void UCP_EscapeMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
