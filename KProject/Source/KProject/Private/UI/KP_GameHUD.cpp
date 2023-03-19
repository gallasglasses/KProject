// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KP_GameHUD.h"
#include "KProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);

void AKP_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EGameState::InPlayerMenu, CreateWidget<UUserWidget>(GetWorld(), PlayerMenuWidgetClass));
	GameWidgets.Add(EGameState::WaitingToStart, CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidgetClass));
	GameWidgets.Add(EGameState::Death, CreateWidget<UUserWidget>(GetWorld(), DeathWidgetClass));
	GameWidgets.Add(EGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &AKP_GameHUD::OnGameStateChanged);
		}
	}
}

void AKP_GameHUD::OnGameStateChanged(EGameState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	UE_LOG(LogGameHUD, Display, TEXT("State: %s"), *UEnum::GetValueAsString(State));
}
