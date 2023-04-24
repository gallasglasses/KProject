// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableActor.h"
#include "QuestSubsystem.h"

ACollectableActor::ACollectableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	//OnDestroyed.AddDynamic(this, &ThisClass::OnDestroyCollectableActor);
}

void ACollectableActor::OnCollectionFinished(AActor* ActorCollectedObject)
{
	NotifyCollectionFinished(this, ActorCollectedObject);
}

void ACollectableActor::OnDestroyCollectableActor(AActor* Actor)
{
	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->RemoveQuestActor(Actor);
}

void ACollectableActor::BeginPlay()
{
	Super::BeginPlay();

	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->AddQuestActor(this, CollectableActorClass);
}