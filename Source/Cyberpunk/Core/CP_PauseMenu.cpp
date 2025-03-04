#include "CP_PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/KismetSystemLibrary.h"

UCP_PauseMenu::UCP_PauseMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCP_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UCP_PauseMenu::OnResumeButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: ResumeButton 위젯이 바인딩되지 않았습니다."));
	}

	if (ExitFromPauseButton)
	{
		ExitFromPauseButton->OnClicked.AddDynamic(this, &UCP_PauseMenu::OnExitFromPauseButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: ExitFromPauseButton 위젯이 바인딩되지 않았습니다."));
	}
}


void UCP_PauseMenu::OnResumeButtonClicked()
{
	// 일시정지 메뉴 제거 (화면에서 숨김)
	RemoveFromParent();
	// 게임 재개 로직 (Unpause 등, 필요하면 여기에 구현)
	UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: Resume Button Clicked"));
}

void UCP_PauseMenu::OnExitFromPauseButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	UE_LOG(LogTemp, Warning, TEXT("CP_PauseMenu: Exit from Pause Button Clicked"));
}