// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KP_ManaComponent.h"
#include "Player/KP_BaseCharacter.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(ManaComponentLog, All, All);

UKP_ManaComponent::UKP_ManaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKP_ManaComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxMana > 0);

	SetMana(MaxMana);

	auto ComponentOwner = Cast<AKP_BaseCharacter>(GetOwner());
	if (ComponentOwner)
	{
		ComponentOwner->OnGiveAnyMana.AddUObject(this, &UKP_ManaComponent::OnGiveAnyMana);
	}

}

void UKP_ManaComponent::OnGiveAnyMana()
{
	if (!GetWorld()) return;

	SetMana(Mana - 10.f);

	GetWorld()->GetTimerManager().ClearTimer(ManaRecoveryTimerHandle);

	if (IsMuggle())
	{
		OnMuggle.Broadcast();
	}
	if (AutoManaRecovery)
	{
		GetWorld()->GetTimerManager().SetTimer(ManaRecoveryTimerHandle, this, &UKP_ManaComponent::ManaUpdate, ManaRecoveryUpdateTime, true, ManaRecoveryDelay);
	}
}

void UKP_ManaComponent::ManaUpdate()
{
	SetMana(Mana + ManaRecoveryModifier);

	if (FMath::IsNearlyEqual(Mana, MaxMana) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ManaRecoveryTimerHandle);
	}
}

void UKP_ManaComponent::SetMana(float NewMana)
{
	const auto NextMana = FMath::Clamp(NewMana, 0.0f, MaxMana);
	const auto ManaDelta = NextMana - Mana;

	UE_LOG(ManaComponentLog, Display, TEXT("Delta %f Mana %f NextMana %f"), ManaDelta, Mana, NextMana);
	Mana = NextMana;
	OnManaChanged.Broadcast(Mana, ManaDelta);
}