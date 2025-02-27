#include "CP_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h" // 위젯 트리 사용을 위한 include
#include "EnhancedInputSubsystems.h" // UInputSubsystem 사용을 위한 include
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
        UE_LOG(LogTemp, Warning, TEXT("StartButton 위젯이 바인딩되지 않았습니다."));
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnExitButtonClicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExitButton 위젯이 바인딩되지 않았습니다."));
    }
}

void UCP_MainMenu::OnStartButtonClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuMap")); // "YourLevelName"을 실제 레벨 이름으로 변경

    // 게임 시작 후 ESC 키 입력 활성화
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // SetInputActionMappingByName 함수가 없으므로, 적절한 함수로 대체팔요
            // InputSubsystem->SetInputActionMappingByName("Pause", EInputEvent::IE_Pressed); // "Pause" 액션 매핑
        }
    }

    // 게임 시작 시 HUD 위젯 표시 (CP_PlayerHUD)
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        TSubclassOf<UCP_PlayerHUD> HUDClass; // CP_PlayerHUD 클래스
        if (HUDClass)
        {
            UCP_PlayerHUD* PlayerHUD = CreateWidget<UCP_PlayerHUD>(PlayerController, HUDClass);
            if (PlayerHUD)
            {
                PlayerHUD->AddToViewport();
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Start Button Clicked"));
}

void UCP_MainMenu::OnExitButtonClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
    UE_LOG(LogTemp, Warning, TEXT("Exit Button Clicked"));
}

void UCP_MainMenu::ShowPauseMenu()
{
    if (PauseMenuWidget)
    {
        PauseMenuWidget->AddToViewport();
        if (ResumeButton)
        {
            ResumeButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnResumeButtonClicked);
        }
        if (ExitFromPauseButton)
        {
            ExitFromPauseButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnExitFromPauseButtonClicked);
        }
    }
    else
    {
        // PauseMenuWidget이 없으면 생성
        PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), LoadObject<UClass>(nullptr, TEXT("/Game/UI/WBP_PauseMenu.WBP_PauseMenu"))); // 실제 경로와 이름으로 변경
        if (PauseMenuWidget)
        {
            ShowPauseMenu(); // 다시 호출하여 Pause 메뉴 표시
        }
    }
}

void UCP_MainMenu::OnResumeButtonClicked()
{
    if (PauseMenuWidget)
    {
        PauseMenuWidget->RemoveFromParent(); // RemoveFromViewport 대신 RemoveFromParent 사용
    }
    // 게임 재개 로직 (Unpause 등)
    UE_LOG(LogTemp, Warning, TEXT("Resume Button Clicked"));
}

void UCP_MainMenu::OnExitFromPauseButtonClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
    UE_LOG(LogTemp, Warning, TEXT("Exit from Pause Button Clicked"));
}