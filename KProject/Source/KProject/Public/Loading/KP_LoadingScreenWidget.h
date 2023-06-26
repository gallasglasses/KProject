#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_LoadingScreenWidget.generated.h"

class UTextBlock;
class UButton;
class UImage;
class UWidgetSwitcher;

UCLASS()
class KPROJECT_API UKP_LoadingScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void FadeInAnimation();

protected:

	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation);

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LoadingText;

	UPROPERTY(meta = (BindWidget))
		UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
		UImage* LoadingImage;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* LoadingSwitcher;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeInAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeOutAnim;

private:

	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void LoadLevel();

	void LevelFinishedLoad(ULevel* Level, UWorld* World);
	FName GetLevelNameFromGameInstance();
};
