// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/KP_CharacterAbilitiesComponent.h"
#include "Abilities/KP_Shield.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(AbilitiesComponentLog, All, All);

UKP_CharacterAbilitiesComponent::UKP_CharacterAbilitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKP_CharacterAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKP_CharacterAbilitiesComponent::SpawnAbility()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	FActorSpawnParameters AbilitySpawnParameters;
	AbilitySpawnParameters.Owner = Character;
	Shield = GetWorld()->SpawnActor<AKP_Shield>(AbilityClass, AbilitySpawnParameters);
	if (Shield)
	{
		UE_LOG(AbilitiesComponentLog, Display, TEXT("Shield"));
		const FAttachmentTransformRules ShieldAttachmentRules(EAttachmentRule::KeepRelative, false);
		Shield->AttachToComponent(Character->GetMesh(), ShieldAttachmentRules, "spine_01"); //spine_01
		Shield->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}
	else
	{
		UE_LOG(AbilitiesComponentLog, Display, TEXT("Shield NULL"));
		return;
	}
}
