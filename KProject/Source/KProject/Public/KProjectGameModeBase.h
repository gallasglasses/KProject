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

	bool SetQuestList(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause());

	virtual bool ClearPause() override;

	void StartGame();
	void Dead();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void TurnOnGlobalGravitySet();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void TurnOffGlobalGravitySet();

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

	EGameWidgetState GameState = EGameWidgetState::WaitingToStart;

	FTimerHandle GameOverTestTimer;// for test only

	void GameOver();	

	void GameTimerTestUpdate(); // for test only

	void SetGameState(EGameWidgetState State);
	void ResetPlayer();
//	void SpawnBots();
};
