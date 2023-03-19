// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/KP_PauseMenuGameWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UKP_PauseMenuGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

	if (UnpauseButton)
	{
		UnpauseButton->OnClicked.AddDynamic(this, &UKP_PauseMenuGameWidget::OnUnpause);
	}
}

void UKP_PauseMenuGameWidget::OnUnpause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
