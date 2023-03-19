// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_PauseMenuGameWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class KPROJECT_API UKP_PauseMenuGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* PauseText;

	UPROPERTY(meta = (BindWidget))
		UButton* UnpauseButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* UnpauseButtonText;
	
private:

	UFUNCTION()
	void OnUnpause();
};
