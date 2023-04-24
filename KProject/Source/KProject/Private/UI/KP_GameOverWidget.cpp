// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/KP_GameOverWidget.h"
#include "KProjectGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(WBPGameOverLog, All, All);

void UKP_GameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (GetWorld())
	{
		const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddUObject(this, &UKP_GameOverWidget::OnGameStateChanged);
		}
	}
}

void UKP_GameOverWidget::OnGameStateChanged(EGameWidgetState State)
{
	if (State == EGameWidgetState::GameOver)
	{
		//TODO: maybe show game ending credits
		ShowGameEndingCredits();
	}
}

void UKP_GameOverWidget::ShowGameEndingCredits()
{
	UE_LOG(WBPGameOverLog, Display, TEXT("************ Ending Credits ************"));
}
