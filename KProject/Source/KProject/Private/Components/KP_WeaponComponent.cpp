// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/KP_WeaponComponent.h"
#include "Weapons/KP_Dagger.h"
#include "Components/KP_HealthComponent.h"
#include "KP_Utils.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(WeaponComponentLog, All, All);

UKP_WeaponComponent::UKP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UKP_WeaponComponent::WeaponAttack()
{
	if(!Weapon) return;

	UE_LOG(WeaponComponentLog, Display, TEXT("WeaponAttack"));
	Weapon->OnStart();
}

void UKP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnWeapon();
}

void UKP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Weapon)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapon = nullptr;
	Super::EndPlay(EndPlayReason);
}

void UKP_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	FActorSpawnParameters ActorSpawnParameters; 
	ActorSpawnParameters.Owner = Character;
	Weapon = GetWorld()->SpawnActor<AKP_Dagger>(WeaponClass, ActorSpawnParameters);
	if (!Weapon) return;

	FAttachmentTransformRules AttacmentRules(EAttachmentRule::KeepRelative, false);
	Weapon->AttachToComponent(Character->GetMesh(),AttacmentRules, WeaponSocketName);
}

void UKP_WeaponComponent::OnWantToStart()
{
	if (Weapon)
	{
		OnWantToStartAttack.Broadcast();
	}
}

void UKP_WeaponComponent::OnWantToStop()
{
	OnWantToStopAttack.Broadcast();
}
