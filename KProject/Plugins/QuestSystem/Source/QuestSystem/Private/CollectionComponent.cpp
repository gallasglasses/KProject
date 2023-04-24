// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionComponent.h"
#include "CollectableObject.h"
#include "CollectableObject.h"
#include "Blueprint/UserWidget.h"

UCollectionComponent::UCollectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCollectionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollectionCompBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCollectionCompEndOverlap);
}

void UCollectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollectionComponent::Collect()
{
	if (ActorToCollect)
	{
		ICollectableObject::Execute_Collect(ActorToCollect, GetOwner());
	}
}

void UCollectionComponent::OnCollectionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UCollectableObject>())
	{
		ActorToCollect = OtherActor;
		if (!CollectMessage)
		{
			if (CollectMessageWidget)
			{
				CollectMessage = CreateWidget<UUserWidget>(GetWorld(), CollectMessageWidget);
			}
		}

		if (CollectMessage && !CollectMessage->IsInViewport())
		{
			CollectMessage->AddToViewport();
		}
	}
}

void UCollectionComponent::OnCollectionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActorToCollect = nullptr;
	if (CollectMessage)
	{
		CollectMessage->RemoveFromViewport();
	}
}