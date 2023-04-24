// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "Objective.h"

AQuest::AQuest()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AQuest::BeginPlay()
{
	Super::BeginPlay();

	// for testing
	 	/*AActor* ParentActor = GetAttachParentActor();
	 	if (ParentActor)
	 	{
	 		TakeQuest(ParentActor);
	 	}*/
}

void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuest::TakeQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];
		if (Objective == nullptr)
		{
			continue;
		}

		Objective->ActivateObjective(Character);
		Objective->bCanBeCompleted = i == 0 || !bKeepObjectivesOrder;
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
	}
	bIsTaken = true;
	OnStatusChanged.Broadcast(this);
}

const TArray<UObjective*>& AQuest::GetObjectives() const
{
	return Objectives;
}

void AQuest::OnObjectiveCompleted(UObjective* Objective)
{
	if (bKeepObjectivesOrder)
	{
		int32 Index;
		if (Objectives.Find(Objective, Index) && Objectives.IsValidIndex(Index + 1))
		{
			Objectives[Index + 1]->bCanBeCompleted = true;
			OnQuestStatusChanged.Broadcast(this);
		}
		else
		{
			bIsCompleted = true;
			OnQuestStatusChanged.Broadcast(this);
		}
	}
	else 
	{
		int32 IncompleteCount = 0;
		for (int32 i = 0; i < Objectives.Num(); i++)
		{
			if (!Objectives[i]->bIsCompleted)
			{
				IncompleteCount++;
			}
		}
		if (IncompleteCount == 0)
		{
			bIsCompleted = true;
		}
		OnQuestStatusChanged.Broadcast(this);
	}
	/*if (IsCompleted())
	{*/
		OnStatusChanged.Broadcast(this);
	//}
}

bool AQuest::IsCompleted()
{
	if (bKeepObjectivesOrder && Objectives.IsValidIndex(Objectives.Num() - 1))
	{
		return Objectives[Objectives.Num() - 1]->bIsCompleted;
	}

	for (auto* Objective : Objectives)
	{
		if (Objective && !Objective->bIsCompleted)
		{
			//bIsCompleted = false;
			return false;
		}
	}
	//bIsCompleted = true;
	return true;
}

bool AQuest::IsAvailable()
{
	if (!bIsTaken && !IsCompleted() && !PreviousQuest)
	{
		return true;
	}
	if (!bIsTaken && !IsCompleted() && PreviousQuest && PreviousQuest->IsCompleted())
	{
		return true;
	}
	return false;

}

void AQuest::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

void AQuest::AddLocationObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

void AQuest::AddCollectionObjective()
{
	Objectives.Add(NewObject<UCollectionObjective>(this));
}

void AQuest::AddKillableObjective()
{
	Objectives.Add(NewObject<UKillableObjective>(this));
}