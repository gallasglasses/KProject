// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

TArray<AActor*> UQuestSubsystem::FindActorsOfClass(TSubclassOf<AActor> ActorClass)
{
	TArray<AActor*> ActorsToReturn;
	for (auto Actor : Actors)
	{
		if (Actor.Value == ActorClass)
		{
			ActorsToReturn.Add(Actor.Key);
		}
	}

	return ActorsToReturn;
}

void UQuestSubsystem::RemoveQuestActor(AActor* QuestActor)
{
	if (Actors.Contains(QuestActor))
	{
		Actors.Remove(QuestActor);
	}
}