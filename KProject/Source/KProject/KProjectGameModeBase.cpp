// Copyright Epic Games, Inc. All Rights Reserved.


#include "KProjectGameModeBase.h"
#include "Player/KP_BaseCharacter.h"
#include "Player/KP_PlayerController.h"
#include "UI/KP_GameHUD.h"
#include "EngineUtils.h"

//#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(KProjectGameModeBaseLog, All, All);

AKProjectGameModeBase::AKProjectGameModeBase()
{
	DefaultPawnClass = AKP_BaseCharacter::StaticClass();
	PlayerControllerClass = AKP_PlayerController::StaticClass();
	HUDClass = AKP_GameHUD::StaticClass();
}

void AKProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	//SpawnBots();

	StartGame();
	SetGameState(EGameState::InProgress);
}

bool AKProjectGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	return false;
}

void AKProjectGameModeBase::GameOver()
{
	UE_LOG(KProjectGameModeBaseLog, Display, TEXT("************ GAME OVER ************"));

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetGameState(EGameState::GameOver);
}

void AKProjectGameModeBase::StartGame()
{
	UE_LOG(KProjectGameModeBaseLog, Display, TEXT("************ START GAME ************"));



	// TODO: trigger for game over
	//GetWorldTimerManager().SetTimer(GameOverTestTimer, this, &AKProjectGameModeBase::GameTimerTestUpdate, 30.f, false); // for test
}

void AKProjectGameModeBase::GameTimerTestUpdate()
{
	GameOver();
	GetWorldTimerManager().ClearTimer(GameOverTestTimer);
}

void AKProjectGameModeBase::SetGameState(EGameState State)
{
	if (GameState == State) return;

	GameState = State;
	OnGameStateChanged.Broadcast(GameState);
} 

//UClass* AKProjectGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
//{
//	if (InController && InController->IsA<AAIController>())
//	{
//		return AIPawnClass;
//	}
//	return Super::GetDefaultPawnClassForController_Implementation(InController);
//}
//
//void AKProjectGameModeBase::SpawnBots()
//{
//	if(!GetWorld()) return;
//
//	for (int32 i = 0; i < GameData.AIPlayersNum; ++i)
//	{
//		FActorSpawnParameters SpawnInfo;
//		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//		const auto KP_AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
//		RestartPlayer(KP_AIController);
//	}
//}
