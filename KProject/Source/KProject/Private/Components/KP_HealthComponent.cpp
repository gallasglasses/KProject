// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/KP_HealthComponent.h"
//#include "Damaging/KP_IceDamageType.h"
//#include "Damaging/KP_FireDamageType.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UKP_HealthComponent::UKP_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UKP_HealthComponent::OnTakeAnyDamage);
	}
	
}

void UKP_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <=0.f || IsDead() || !GetWorld()) return;

	UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f"), Damage);
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UKP_HealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	/*if (DamageType)
	{
		if (DamageType->IsA<UKP_FireDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("It's so hot!"));
		}
		else if (DamageType->IsA<UKP_IceDamageType>())
		{
			UE_LOG(HealthComponentLog, Display, TEXT("It's so cold!"));
		}
	}*/
}

void UKP_HealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UKP_HealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	UE_LOG(HealthComponentLog, Display, TEXT("Delta %f Health %f NextHealth %f"), HealthDelta, Health, NextHealth);
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UKP_HealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull())
	{
		return false;
	}
	SetHealth(Health + HealthAmount);
	return true;
}

bool UKP_HealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}
