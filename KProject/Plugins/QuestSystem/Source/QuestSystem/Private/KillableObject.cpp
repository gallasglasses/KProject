// Fill out your copyright notice in the Description page of Project Settings.

#include "KillableObject.h"

void IKillableObject::NotifyKillingFinished(AActor* KillableObject, AActor* ActorKilledObject)
{
	if (OnKillingFinished.IsBound())
	{
		OnKillingFinished.Broadcast(KillableObject, ActorKilledObject);
		UE_LOG(LogTemp, Display, TEXT("IKillableObject::NotifyKillingFinished"));

	}
}