// Fill out your copyright notice in the Description page of Project Settings.

#include "KillableActor.h"
#include "QuestSubsystem.h"

AKillableActor::AKillableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	//OnDestroyed.AddDynamic(this, &ThisClass::OnDestroyAKillableActor);
}

void AKillableActor::OnKillingFinished(AActor* ActorKilledObject)
{
	NotifyKillingFinished(this, ActorKilledObject);
}

void AKillableActor::OnDestroyKillableActor(AActor* Actor)
{
	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->RemoveQuestActor(Actor);
}

void AKillableActor::BeginPlay()
{
	Super::BeginPlay();

	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->AddQuestActor(this, KillableActorClass);
}