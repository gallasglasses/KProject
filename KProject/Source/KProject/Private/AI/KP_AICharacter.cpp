// Fill out your copyright notice in the Description page of Project Settings.

//custom h
#include "AI/KP_AICharacter.h"
#include "AI/KP_AIController.h"

#include "Components/KP_AIMovementComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(AICharacterLog, All, All);

AKP_AICharacter::AKP_AICharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UKP_AIMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AKP_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	}
}

void AKP_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
}

void AKP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AKP_AICharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AKP_AICharacter::OnInteractionFinished(AActor* ActorInteractedWithObject)
{
	NotifyInteractionFinished(this, ActorInteractedWithObject);
}
