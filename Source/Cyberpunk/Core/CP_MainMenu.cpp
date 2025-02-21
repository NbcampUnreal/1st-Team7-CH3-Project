#include "CP_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h" // ���� Ʈ�� ����� ���� include
#include "EnhancedInputSubsystems.h" // UInputSubsystem ����� ���� include
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
        UE_LOG(LogTemp, Warning, TEXT("StartButton ������ ���ε����� �ʾҽ��ϴ�."));
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UCP_MainMenu::OnExitButtonClicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExitButton ������ ���ε����� �ʾҽ��ϴ�."));
    }
}

void UCP_MainMenu::OnStartButtonClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuMap"));

    // ���� ���� �� ESC Ű �Է� Ȱ��ȭ
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // InputSubsystem->SetInputActionMappingByName("Pause", EInputEvent::IE_Pressed); // "Pause" �׼� ����
        }
    }

    // ���� ���� �� HUD ���� ǥ�� (CP_PlayerHUD)
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        TSubclassOf<UCP_PlayerHUD> HUDClass; // CP_PlayerHUD Ŭ����
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
        // PauseMenuWidget�� ������ ����
        PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), LoadObject<UClass>(nullptr, TEXT("/Game/UI/WBP_PauseMenu.WBP_PauseMenu"))); // ���� ��ο� �̸����� ����
        if (PauseMenuWidget)
        {
            ShowPauseMenu(); // �ٽ� ȣ���Ͽ� Pause �޴� ǥ��
        }
    }
}

void UCP_MainMenu::OnResumeButtonClicked()
{
    if (PauseMenuWidget)
    {
        PauseMenuWidget->RemoveFromParent(); // RemoveFromViewport ��� RemoveFromParent ���
    }
    // ���� �簳 ���� (Unpause ��)
    UE_LOG(LogTemp, Warning, TEXT("Resume Button Clicked"));
}

void UCP_MainMenu::OnExitFromPauseButtonClicked()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
    UE_LOG(LogTemp, Warning, TEXT("Exit from Pause Button Clicked"));
}