// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestListComponent.h"
#include "CurrentObjectives.h"
#include "Objective.h"
#include "Quest.h"

UQuestListComponent::UQuestListComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentObjectivesWidget)
	{
		UCurrentObjectives* ObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(), CurrentObjectivesWidget);
		OnActiveQuestChanged.AddUObject(ObjectivesWidget, &UCurrentObjectives::SetCurrentObjectives);
		ObjectivesWidget->AddToViewport();
	}
}


void UQuestListComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestListComponent::AddQuest(AQuest* Quest)
{
	if (Quest == nullptr)
	{
		return;
	}
	if (ActiveQuest->IsCompleted() || ActiveQuest == nullptr)
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
	}

	AcceptedQuests.AddUnique(Quest);
	Quest->TakeQuest(GetOwner());
	Quest->OnQuestStatusChanged.AddLambda([this](AQuest* ChangedQuest)
		{
			if (ActiveQuest == ChangedQuest )
			{
				if (OnActiveQuestChanged.IsBound())
				{
					OnActiveQuestChanged.Broadcast(ChangedQuest);
				}
			}
		});
}

const TArray<AQuest*>& UQuestListComponent::GetQuests() const
{
	return AcceptedQuests;
}

AQuest* UQuestListComponent::GetActiveQuest() const
{
	return ActiveQuest;
}

void UQuestListComponent::SetActiveQuest(AQuest* Quest)
{
	if (AcceptedQuests.Contains(Quest) && !Quest->IsCompleted())
	{
		ActiveQuest = Quest;
		if (OnActiveQuestChanged.IsBound())
		{
			OnActiveQuestChanged.Broadcast(Quest);
		}
	}
}

TArray<AActor*> UQuestListComponent::GetInteractableQuestsObjects()
{
	TArray<AActor*> InteractableQuestsObjects;
	const auto QuestsObjectives = ActiveQuest->GetObjectives();
	for (int32 i = 0; i < QuestsObjectives.Num(); i++)
	{
		const auto InteractableObject = Cast<UInteractionObjective>(QuestsObjectives[i]);
		if (QuestsObjectives[i] && InteractableObject)
		{
			InteractableQuestsObjects.Add(InteractableObject->Target);
		}
	}
	return InteractableQuestsObjects;
}