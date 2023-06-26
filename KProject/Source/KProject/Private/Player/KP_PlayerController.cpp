// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KP_PlayerController.h"
#include "Player/KP_BaseCharacter.h"
#include "UI/KP_GameHUD.h"
#include "KProjectGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "QuestList.h"

DEFINE_LOG_CATEGORY_STATIC(KP_PlayerControllerLog, All, All);

AKP_PlayerController::AKP_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AKP_PlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(bPause, CanUnpauseDelegate);
	return PauseSet;
}

void AKP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseMenuGame", IE_Pressed, this, &AKP_PlayerController::OnPauseGame);
	InputComponent->BindAction("ToggleQuestList", IE_Pressed, this, &AKP_PlayerController::ToggleQuestList);
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
			UE_LOG(KP_PlayerControllerLog, Display, TEXT("OnDead.AddUObject this, &AKP_PlayerController::OnDead"));
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

void AKP_PlayerController::ToggleQuestList()
{

	UE_LOG(KP_PlayerControllerLog, Display, TEXT("*******************************"));
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto PlayerHUD = Cast<AKP_GameHUD>(GetHUD());
	const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SetQuestList(this);
	}

	UE_LOG(KP_PlayerControllerLog, Display, TEXT("Turn on QuestList"));
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

void AKP_PlayerController::OnGameStateChanged(EGameWidgetState State)
{
	if (State == EGameWidgetState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}
