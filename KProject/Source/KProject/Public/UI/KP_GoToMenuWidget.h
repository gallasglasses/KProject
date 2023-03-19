// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_GoToMenuWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class KPROJECT_API UKP_GoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* GoToMenuButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GoToMenuText;

private: 

	UFUNCTION()
		void OnGoToMainMenu();
};
