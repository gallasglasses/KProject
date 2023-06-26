// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/KP_DeathWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "KP_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(WBPDeathLog, All, All);

void UKP_DeathWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*if (LoadLastSaveButton)
	{
		LoadLastSaveButton->OnClicked.AddDynamic(this, &UKP_DeathWidget::LoadMostRecentSave);
	}

	if (LoadSavedButton)
	{
		LoadSavedButton->OnClicked.AddDynamic(this, &UKP_DeathWidget::LoadSaved);
	}*/
}

//void UKP_DeathWidget::LoadMostRecentSave()
//{
//	UE_LOG(WBPDeathLog, Display, TEXT("************ Load Most Recent Save ************"));
//}
//
//void UKP_DeathWidget::LoadSaved()
//{
//	UE_LOG(WBPDeathLog, Display, TEXT("************ Load Saved ************"));
//
//}

void UKP_DeathWidget::OnRestartGame() // for hard/master game difficulty
{
	UE_LOG(WBPDeathLog, Display, TEXT("************ OnRestartGame ************"));

	if (!GetWorld()) return;

	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	if (KP_GameInstance->GetMainLevelName().IsNone())
	{
		UE_LOG(WBPDeathLog, Error, TEXT("Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, KP_GameInstance->GetMainLevelName());
}
