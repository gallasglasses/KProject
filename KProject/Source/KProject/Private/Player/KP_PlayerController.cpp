// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KP_PlayerController.h"
#include "Player/KP_BaseCharacter.h"
#include "KProjectGameModeBase.h"
#include "GameFramework/GameModeBase.h"

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

void AKP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &AKP_PlayerController::OnGameStateChanged);
		}

		const auto PlayerPawn = Cast<AKP_BaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerPawn)
		{
			PlayerPawn->OnDead.AddUObject(this, &AKP_PlayerController::OnDead);
		}
	}
}

void AKP_PlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SetPause(this);
	}

	//TODO: Find and add some situations for check to pause/unpause. 
	/**
	 * SetPause: CanUnpauseDelegate
	 * Adds the delegate to the list if the player Controller has the right to pause
	 * the game. The delegate is called to see if it is ok to unpause the game, e.g.
	 * the reason the game was paused has been cleared.
	 * @param PC the player Controller to check for admin privs
	 * @param CanUnpauseDelegate the delegate to query when checking for unpause
	 */
}

void AKP_PlayerController::OnDead()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->Dead();
	}
}

void AKP_PlayerController::OnGameStateChanged(EGameState State)
{
	if (State == EGameState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
