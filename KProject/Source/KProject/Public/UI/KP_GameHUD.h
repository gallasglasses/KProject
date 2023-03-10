// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KP_CoreTypes.h"
#include "KP_GameHUD.generated.h"

class UUserWidget;

UCLASS()
class KPROJECT_API AKP_GameHUD : public AHUD
{
	GENERATED_BODY()
	
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

private:
		
		void OnGameStateChanged(EGameState State);
};
