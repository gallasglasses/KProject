// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/KP_MenuHUD.h"
#include "Menu/UI/KP_MenuWidget.h"

void AKP_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UKP_MenuWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->ShowOpening();
		}
	}
}
