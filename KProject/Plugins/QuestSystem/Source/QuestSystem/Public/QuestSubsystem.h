// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestSubsystem.generated.h"

UCLASS()
class QUESTSYSTEM_API UQuestSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TMap<AActor*, TSubclassOf<AActor>> Actors;



public:

	void AddQuestActor(AActor* QuestActor, TSubclassOf<AActor> ActorClass) { Actors.Add(QuestActor, ActorClass); }

	TArray<AActor*> FindActorsOfClass(TSubclassOf<AActor> ActorClass);

	void RemoveQuestActor(AActor* QuestActor);
};