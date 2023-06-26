// Fill out your copyright notice in the Description page of Project Settings.


#include "Loading/KP_LoadingPlayerController.h"

void AKP_LoadingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
