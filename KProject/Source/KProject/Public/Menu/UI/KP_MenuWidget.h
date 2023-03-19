// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_MenuWidget.generated.h"

class UTextBlock;
class UButton;
class USoundCue;

UCLASS()
class KPROJECT_API UKP_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ShowOpening();

protected:

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation);

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MenuText;

	UPROPERTY(meta = (BindWidget))
		UButton* NewGameButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NewGameText;

	UPROPERTY(meta = (BindWidget))
		UButton* LoadSavedButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LoadSavedText;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* QuitText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OpeningAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EndingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* MenuSound;

private:

	UFUNCTION()
	void OnStartNewGame();

	UFUNCTION()
	void OnLoadSaved();

	UFUNCTION()
	void OnQuitGame();
};
