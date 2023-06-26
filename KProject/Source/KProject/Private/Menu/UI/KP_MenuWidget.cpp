// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/KP_MenuWidget.h"
#include "KP_GameInstance.h"

#include "Components/Button.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(WBPMenuLog, All, All);

void UKP_MenuWidget::ShowOpening()
{
	PlayAnimation(OpeningAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), MenuSound);
}

void UKP_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddDynamic(this, &UKP_MenuWidget::OnStartNewGame);
	}

	/*if (LoadSavedButton)
	{
		LoadSavedButton->OnClicked.AddDynamic(this, &UKP_MenuWidget::OnLoadSaved);
	}*/

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UKP_MenuWidget::OnQuitGame);
	}
}

void UKP_MenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation != EndingAnimation) return;

	if (!GetWorld()) return;
	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	if (KP_GameInstance->GetLevel(EGameLevel::MainLevel).IsNull())
	{
		UE_LOG(WBPMenuLog, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, FName(KP_GameInstance->GetLevel(EGameLevel::MainLevel).ToSoftObjectPath().GetAssetName())); //this, KP_GameInstance->GetMainLevelName()
}

void UKP_MenuWidget::OnStartNewGame()
{
	PlayAnimation(EndingAnimation);
}

void UKP_MenuWidget::OnLoadSaved()
{
	UE_LOG(WBPMenuLog, Display, TEXT("************** On Load Saved *************"));
}

void UKP_MenuWidget::OnQuitGame()
{
	UE_LOG(WBPMenuLog, Display, TEXT("************** OnQuitGame *************"));
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
