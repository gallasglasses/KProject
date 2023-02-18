// Fill out your copyright notice in the Description page of Project Settings.


#include "KP_CharacterMovementComponent.h"
#include "Player/KP_BaseCharacter.h"

float UKP_CharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AKP_BaseCharacter* Player = Cast<AKP_BaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
