// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KP_GameHUD.h"
#include "KProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Player/KP_BaseCharacter.h"
#include "QuestList.h"
#include "KP_Utils.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);

UUserWidget* AKP_GameHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const EGameWidgetState State, const int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (CurrentWidget)
	{
		if (State == EGameWidgetState::QuestList)
		{
			const auto Player = Cast<AKP_BaseCharacter>(GetOwningPawn());
			const auto QuestList = Cast<UQuestList>(CurrentWidget);
			QuestList->Init(KP_Utils::GetPlayerComponent<UQuestListComponent>(Player));
		}
		CurrentWidget->AddToViewport(ZOrder);
	}
	return CurrentWidget;
}

void AKP_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UUserWidget>* GameWidgetClass = GameWidgets.Find(EGameWidgetState::InProgress);
	if (GameWidgetClass && *GameWidgetClass)
	{
		CreateWidgetByClass(*GameWidgetClass, EGameWidgetState::InProgress);
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

UUserWidget* AKP_GameHUD::ShowWidget(const EGameWidgetState WidgetID, const int32 ZOrder)
{
	TSubclassOf<UUserWidget>* MenuWidgetClass = GameWidgets.Find(WidgetID);
	if (MenuWidgetClass && *MenuWidgetClass)
	{
		CreateWidgetByClass(*MenuWidgetClass, WidgetID, ZOrder);
	}
	return CurrentWidget;
}

void AKP_GameHUD::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void AKP_GameHUD::OnGameStateChanged(EGameWidgetState State)
{
	HideWidget();
	ShowWidget(State);
	
	UE_LOG(LogGameHUD, Display, TEXT("State: %s"), *UEnum::GetValueAsString(State));
}
