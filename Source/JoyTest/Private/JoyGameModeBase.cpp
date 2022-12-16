// JoyTest Game


#include "JoyGameModeBase.h"
#include "Player/JoyCharacter.h"
#include "Player/JoyPlayerController.h"

AJoyGameModeBase::AJoyGameModeBase()
{
    DefaultPawnClass = AJoyCharacter::StaticClass();
    PlayerControllerClass = AJoyPlayerController::StaticClass();
}

