// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KP_CoreTypes.h"
//#include "AI/KP_AIController.h"
#include "KProjectGameModeBase.generated.h"

//class AAIController;

UCLASS()
class KPROJECT_API AKProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKProjectGameModeBase();

	FOnGameStateChangedSignature OnGameStateChanged;

	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

//	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Classes)
//	UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
//
//protected:
//
//	UPROPERTY(EditDefaultsOnly, Category = "Game")
//	TSubclassOf<AKP_AIController> AIControllerClass;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Game")
//	TSubclassOf<APawn> AIPawnClass;
//
//	UPROPERTY(EditDefaultsOnly, Category = "Game")
//	FGameData GameData;

private:

	EGameState GameState = EGameState::WaitingToStart;

	FTimerHandle GameOverTestTimer;// for test only

	void GameOver();	
	void StartGame();

	void GameTimerTestUpdate(); // for test only

	void SetGameState(EGameState State);

//	void SpawnBots();
};
