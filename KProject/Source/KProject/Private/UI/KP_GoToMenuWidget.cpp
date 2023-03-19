// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KP_GoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "KP_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(WBPGoToMenuLog, All, All);

void UKP_GoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UKP_GoToMenuWidget::OnGoToMainMenu);
	}
}

void UKP_GoToMenuWidget::OnGoToMainMenu()
{
	if (!GetWorld()) return;

	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	if (KP_GameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(WBPGoToMenuLog, Error, TEXT("Menu Level name is NONE"));
		return;
	}
	UE_LOG(WBPGoToMenuLog, Display, TEXT("************ Quit To Main Menu ************"));
	UGameplayStatics::OpenLevel(this, KP_GameInstance->GetMenuLevelName());
}
