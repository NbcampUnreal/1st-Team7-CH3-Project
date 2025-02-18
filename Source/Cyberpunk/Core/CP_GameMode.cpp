#include "Core/CP_GameMode.h"
#include "Character/CP_Player.h"
#include "Character/CP_PlayerController.h"
#include "Core/CP_GameState.h"


ACP_GameMode::ACP_GameMode()
{
	DefaultPawnClass = ACP_Player::StaticClass();
	PlayerControllerClass = ACP_PlayerController::StaticClass();
	GameStateClass = ACP_GameState::StaticClass();
}
