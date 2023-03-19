// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/KP_MenuGameModeBase.h"
#include "Menu/KP_MenuPlayerController.h"
#include "Menu/UI/KP_MenuHUD.h"

AKP_MenuGameModeBase::AKP_MenuGameModeBase()
{
	PlayerControllerClass = AKP_MenuPlayerController::StaticClass();
	HUDClass = AKP_MenuHUD::StaticClass();
}