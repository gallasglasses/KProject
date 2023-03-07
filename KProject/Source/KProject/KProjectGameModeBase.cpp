// Copyright Epic Games, Inc. All Rights Reserved.


#include "KProjectGameModeBase.h"
#include "Player/KP_BaseCharacter.h"
#include "Player/KP_PlayerController.h"
#include "UI/KP_GameHUD.h"

//#include "AIController.h"

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
