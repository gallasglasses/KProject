// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KP_HealthPickup.h"
#include "Components/KP_HealthComponent.h"
#include "KP_Utils.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthPickupLog, All, All);

AKP_HealthPickup::AKP_HealthPickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->IgnoreActorWhenMoving(GetOwner(), true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

bool AKP_HealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = KP_Utils::GetPlayerComponent<UKP_HealthComponent>(PlayerPawn);
	if (!HealthComponent)
	{
		return false;
	}
	return HealthComponent->TryToAddHealth(HealthAmount);
}
