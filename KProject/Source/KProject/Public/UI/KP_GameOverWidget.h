// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_CoreTypes.h"
#include "KP_GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class KPROJECT_API UKP_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameOverText;

private:

	void OnGameStateChanged(EGameState State);
	void ShowGameEndingCredits();
};
