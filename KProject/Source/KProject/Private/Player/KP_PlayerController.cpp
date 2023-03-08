// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KP_PlayerController.h"
#include "Gameframework/GameModeBase.h"

AKP_PlayerController::AKP_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseMenuGame", IE_Pressed, this, &AKP_PlayerController::OnPauseGame);
}

void AKP_PlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}
