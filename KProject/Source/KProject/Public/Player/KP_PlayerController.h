// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KP_CoreTypes.h"
#include "KP_PlayerController.generated.h"

UCLASS()
class KPROJECT_API AKP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public: 

	AKP_PlayerController();

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void OnPauseGame();

private:
	
	void OnGameStateChanged(EGameState State);
	void OnDead();
};
