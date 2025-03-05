#include "Core/CP_DeadMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UCP_DeadMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Exit_Button)
	{
		Exit_Button->OnClicked.AddDynamic(this, &UCP_DeadMenu::OnExitButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: ExitFromPauseButton 위젯이 바인딩되지 않았습니다."));
	}
}

void UCP_DeadMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: Exit from Pause Button Clicked"));
}
