// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KP_CoreTypes.h"
#include "KP_GameInstance.generated.h"

class USoundCue;
class USoundMix;

UCLASS()
class KPROJECT_API UKP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FName GetStartupLevelName() const { return StartupLevelName;}
	FName GetMenuLevelName() const { return MenuLevelName;}

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	TMap<EGameLocation, USoundCue*> LocationMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		USoundMix* DefaultSoundMix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		USoundMix* DialogueSoundMix;

};
