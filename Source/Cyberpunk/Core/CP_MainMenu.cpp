#include "CP_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "CP_PlayerHUD.h"
#include "Kismet/KismetSystemLibrary.h"

UCP_MainMenu::UCP_MainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCP_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnStartButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_MainMenu: StartButton 위젯이 바인딩되지 않았습니다."));
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnExitButtonClicked);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CP_MainMenu: ExitButton 위젯이 바인딩되지 않았습니다."));
	}
}

void UCP_MainMenu::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Demo_Map_Final"));

	// 게임 시작 시 HUD 위젯 표시 (CP_PlayerHUD)
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		TSubclassOf<UCP_PlayerHUD> HUDClass = UCP_PlayerHUD::StaticClass();
		if (HUDClass)
		{
			UCP_PlayerHUD* PlayerHUD = CreateWidget<UCP_PlayerHUD>(PlayerController, HUDClass);
			if (PlayerHUD)
			{
				PlayerHUD->AddToViewport();
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("CP_MainMenu: Start Button Clicked"));
}

void UCP_MainMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	UE_LOG(LogTemp, Warning, TEXT("CP_MainMenu: Exit Button Clicked"));
}