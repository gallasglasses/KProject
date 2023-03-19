// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/KP_PlayerUIWidget.h"
#include "Components/KP_HealthComponent.h"
#include "Components/KP_StaminaComponent.h"
#include "Components/KP_ManaComponent.h"
#include "Player/KP_PlayerController.h"
#include "KP_Utils.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UKP_PlayerUIWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	HealthProgressBar->SetFillColorAndOpacity(HealthProgressBarColor);
	ManaProgressBar->SetFillColorAndOpacity(ManaProgressBarColor);
	StaminaProgressBar->SetFillColorAndOpacity(StaminaProgressBarColor);
}

float UKP_PlayerUIWidget::GetHealthPercent() const
{
	const auto HealthComponent = KP_Utils::GetPlayerComponent<UKP_HealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent)
	{
		return 0.0f;
	}
	return HealthComponent->GetHealthPercent();
}

float UKP_PlayerUIWidget::GetStaminaPercent() const
{
	const auto StaminaComponent = KP_Utils::GetPlayerComponent<UKP_StaminaComponent>(GetOwningPlayerPawn());
	if (!StaminaComponent)
	{
		return 0.0f;
	}
	return StaminaComponent->GetStaminaPercent();
}

float UKP_PlayerUIWidget::GetManaPercent() const
{
	const auto ManaComponent = KP_Utils::GetPlayerComponent<UKP_ManaComponent>(GetOwningPlayerPawn());
	if (!ManaComponent)
	{
		return 0.0f;
	}
	return ManaComponent->GetManaPercent();
}

bool UKP_PlayerUIWidget::IsPlayerAlive() const
{
	const auto HealthComponent = KP_Utils::GetPlayerComponent<UKP_HealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UKP_PlayerUIWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

//void UKP_PlayerUIWidget::OnTakeDamage()
//{
//	
//}

void UKP_PlayerUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const auto HealthComponent = KP_Utils::GetPlayerComponent<UKP_HealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UKP_PlayerUIWidget::OnHealthChanged);
	}
	
	const auto StaminaComponent = KP_Utils::GetPlayerComponent<UKP_StaminaComponent>(GetOwningPlayerPawn());
	if (StaminaComponent)
	{
		StaminaComponent->OnStaminaChanged.AddUObject(this, &UKP_PlayerUIWidget::OnStaminaChanged);
	}

	const auto ManaComponent = KP_Utils::GetPlayerComponent<UKP_ManaComponent>(GetOwningPlayerPawn());
	if (ManaComponent)
	{
		ManaComponent->OnManaChanged.AddUObject(this, &UKP_PlayerUIWidget::OnManaChanged);
	}
}

void UKP_PlayerUIWidget::SetHealthPercent(float HealthPercent)
{
	if (!HealthProgressBar)
	{
		return;
	}

	HealthProgressBar->SetPercent(HealthPercent);
}

void UKP_PlayerUIWidget::SetStaminaPercent(float StaminaPercent)
{
	if (!StaminaProgressBar)
	{
		return;
	}

	StaminaProgressBar->SetPercent(StaminaPercent);
}

void UKP_PlayerUIWidget::SetManaPercent(float ManaPercent)
{
	if (!ManaProgressBar)
	{
		return;
	}

	ManaProgressBar->SetPercent(ManaPercent);
}

void UKP_PlayerUIWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();

		if(!IsAnimationPlaying(DamageAnimation))
		{
			PlayAnimation(DamageAnimation);
		}
	}

	SetHealthPercent(GetHealthPercent());
}

void UKP_PlayerUIWidget::OnStaminaChanged(float Stamina, float StaminaDelta)
{
	SetStaminaPercent(GetStaminaPercent());
}

void UKP_PlayerUIWidget::OnManaChanged(float Mana, float ManaDelta)
{
	SetManaPercent(GetManaPercent());
}
