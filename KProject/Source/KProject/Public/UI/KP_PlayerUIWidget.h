// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KP_PlayerUIWidget.generated.h"

class UProgressBar;
class UImage;

UCLASS()
class KPROJECT_API UKP_PlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetStaminaPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetManaPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual bool Initialize() override;

	void SetHealthPercent(float HealthPercent);

	void SetStaminaPercent(float StaminaPercent);

	void SetManaPercent(float ManaPercent);

protected:

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ManaProgressBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
		UImage* StatusImage;

	UPROPERTY(meta = (BindWidget))
		UImage* DamageImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor HealthProgressBarColor = FLinearColor::Green;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor ManaProgressBarColor = FLinearColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FLinearColor StaminaProgressBarColor = FLinearColor::Yellow;

	virtual void NativePreConstruct() override;

private:

	void OnHealthChanged(float Health, float HealthDelta);
	void OnStaminaChanged(float Stamina, float StaminaDelta);
	void OnManaChanged(float Mana, float ManaDelta);
};
