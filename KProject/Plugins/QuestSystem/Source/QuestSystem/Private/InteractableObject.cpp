// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObject.h"

void IInteractableObject::NotifyInteractionFinished(AActor* InteractableObject, AActor* ActorInteractedWithObject)
{
	if (OnInteractionFinished.IsBound())
	{
		OnInteractionFinished.Broadcast(InteractableObject, ActorInteractedWithObject);
	}
}