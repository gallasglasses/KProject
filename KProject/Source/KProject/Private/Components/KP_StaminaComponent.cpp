// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/KP_StaminaComponent.h"
#include "Player/KP_BaseCharacter.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(StaminaComponentLog, All, All);

UKP_StaminaComponent::UKP_StaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKP_StaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxStamina > 0);

	SetStamina(MaxStamina);

	auto ComponentOwner = Cast<AKP_BaseCharacter>(GetOwner());
	if (ComponentOwner)
	{
		ComponentOwner->OnGiveAnyStamina.AddUObject(this, &UKP_StaminaComponent::OnGiveAnyStamina);
	}
	
}

void UKP_StaminaComponent::OnGiveAnyStamina()
{
	if (!GetWorld()) return;

	SetStamina(Stamina - 0.25f);

	GetWorld()->GetTimerManager().ClearTimer(StaminaRecoveryTimerHandle);

	if (IsExhausted())
	{
		OnExhausted.Broadcast();
	}
	if (AutoStaminaRecovery)
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRecoveryTimerHandle, this, &UKP_StaminaComponent::StaminaUpdate, StaminaRecoveryUpdateTime, true, StaminaRecoveryDelay);
	}
}

void UKP_StaminaComponent::StaminaUpdate()
{
	SetStamina(Stamina + StaminaRecoveryModifier);

	if (FMath::IsNearlyEqual(Stamina, MaxStamina) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoveryTimerHandle);
	}
}

void UKP_StaminaComponent::SetStamina(float NewStamina)
{
	const auto NextStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
	const auto StaminaDelta = NextStamina - Stamina;

	UE_LOG(StaminaComponentLog, Display, TEXT("Delta %f Stamina %f NextStamina %f"), StaminaDelta, Stamina, NextStamina);
	Stamina = NextStamina;
	OnStaminaChanged.Broadcast(Stamina, StaminaDelta);
}