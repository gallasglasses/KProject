// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InteractableObject.h"
#include "Blueprint/UserWidget.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractionCompBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractionCompEndOverlap);
	
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::Interact()
{
	if (ActorToInteract)
	{
		UE_LOG(LogTemp, Display, TEXT("UInteractionComponent::Interact()"));

		HideInteractMessage();
		IInteractableObject::Execute_Interact(ActorToInteract, GetOwner());
	}
}

void UInteractionComponent::OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractableObject>())
	{
		ActorToInteract = OtherActor;

		if (!InteractMessage)
		{
			if (InteractMessageWidget)
			{
				InteractMessage = CreateWidget<UUserWidget>(GetWorld(), InteractMessageWidget);
			}
		}

		if (InteractMessage && !InteractMessage->IsInViewport())
		{
			InteractMessage->AddToViewport();
		}
	}
}

void UInteractionComponent::OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActorToInteract = nullptr;
	if (InteractMessage && InteractMessage->IsInViewport())
	{
		InteractMessage->RemoveFromViewport();
	}
}

void UInteractionComponent::HideInteractMessage()
{
	if (InteractMessage && InteractMessage->IsInViewport())
	{
		InteractMessage->RemoveFromViewport();
	}
}