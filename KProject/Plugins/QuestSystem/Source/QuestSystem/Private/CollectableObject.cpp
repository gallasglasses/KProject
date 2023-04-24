// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableObject.h"

void ICollectableObject::NotifyCollectionFinished(AActor* CollectableObject, AActor* ActorCollectedObject)
{
	if (OnCollectionFinished.IsBound())
	{
		OnCollectionFinished.Broadcast(CollectableObject, ActorCollectedObject);
	}
}