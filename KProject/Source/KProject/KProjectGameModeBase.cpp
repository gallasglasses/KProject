// Copyright Epic Games, Inc. All Rights Reserved.


#include "KProjectGameModeBase.h"
#include "Player/KP_BaseCharacter.h"
#include "Player/KP_PlayerController.h"

AKProjectGameModeBase::AKProjectGameModeBase()
{
	DefaultPawnClass = AKP_BaseCharacter::StaticClass();
	PlayerControllerClass = AKP_PlayerController::StaticClass();
}