// Fill out your copyright notice in the Description page of Project Settings.


#include "KillingComponent.h"
#include "KillableObject.h"

UKillingComponent::UKillingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UKillingComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnKillingCompBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnKillingCompEndOverlap);
	
}

void UKillingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UKillingComponent::OnKillingCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UKillableObject>())
	{
		ActorToKill = OtherActor;
		UE_LOG(LogTemp, Display, TEXT("OnKillingCompBeginOverlap"));

	}
}

void UKillingComponent::OnKillingCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*ActorToKill = nullptr;
	UE_LOG(LogTemp, Display, TEXT("ActorToKill = nullptr"));*/

}

void UKillingComponent::Kill()
{
	if (ActorToKill)
	{
		UE_LOG(LogTemp, Display, TEXT(" UKillingComponent::Kill()"));
		IKillableObject::Execute_Kill(ActorToKill, GetOwner());
	}
	ActorToKill = nullptr;
}

