// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/KP_PhysicsMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PhysicsMovementLog, All, All);

UKP_PhysicsMovementComponent::UKP_PhysicsMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void UKP_PhysicsMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UKP_PhysicsMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	FVector NewActorLocation = Owner->GetActorLocation() + Velocity * DeltaTime + Gravity * FMath::Square(DeltaTime) / 2.f;
	Velocity += Gravity * DeltaTime;
	//UE_LOG(PhysicsMovementLog, Display, TEXT("Velocity PM: %s"), *Velocity.ToString());
	Owner->SetActorLocation(NewActorLocation, true);
}

