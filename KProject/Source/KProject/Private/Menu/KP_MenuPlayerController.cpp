// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/KP_MenuPlayerController.h"

void AKP_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;	
}