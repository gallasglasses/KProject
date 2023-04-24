// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_CoreTypes.h"
#include "KP_DeathWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class KPROJECT_API UKP_DeathWidget : public UUserWidget
{
	GENERATED_BODY()

public:


protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DeathText;

	//UPROPERTY(meta = (BindWidget))
	//	UButton* LoadLastSaveButton;

	//UPROPERTY(meta = (BindWidget))
	//	UTextBlock* LoadLastSaveText;

	//UPROPERTY(meta = (BindWidget))
	//	UButton* LoadSavedButton;

	//UPROPERTY(meta = (BindWidget))
	//	UTextBlock* LoadSavedText;

private:

	/*UFUNCTION()
	void LoadMostRecentSave();

	UFUNCTION()
	void LoadSaved();*/

	UFUNCTION()
	void OnRestartGame();
	
};
