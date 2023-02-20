// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KP_GameHUD.h"

#include "Blueprint/UserWidget.h"

void AKP_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}