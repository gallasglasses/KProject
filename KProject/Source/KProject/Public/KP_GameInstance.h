// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KP_CoreTypes.h"
#include "Engine/World.h"
#include "KP_GameInstance.generated.h"

class USoundCue;
class USoundMix;

UCLASS()
class KPROJECT_API UKP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FName GetMainLevelName() const { return MainLevelName;};
	TSoftObjectPtr<UWorld> GetLevel(EGameLevel NewLevel) const;
	FName GetMenuLevelName() const { return MenuLevelName;};
	FName GetLoadingLevelName() const { return LoadingLevelName;};

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName MainLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName LoadingLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Transient, BlueprintReadOnly, Category = "Levels")
	TMap<EGameLevel, TSoftObjectPtr<UWorld>> Levels;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	TMap<EGameLocation, USoundCue*> LocationMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		USoundMix* DefaultSoundMix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
		USoundMix* DialogueSoundMix;

};
