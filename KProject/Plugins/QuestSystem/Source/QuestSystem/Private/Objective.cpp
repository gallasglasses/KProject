// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "InteractableObject.h"
#include "CollectableObject.h"
#include "KillableObject.h"
#include "LocationMarker.h"
#include "QuestSubsystem.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Interact;
	WorldTargetName = GET_MEMBER_NAME_CHECKED(UInteractionObjective, Target);
}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<IInteractableObject>(Target))
	{
		InteractTarget->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			});
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Location;
	WorldTargetName = GET_MEMBER_NAME_CHECKED(ULocationObjective, Marker);
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<ILocationMarker>(Marker))
	{
		InteractTarget->OnLocationReached.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
					Object->Destroy();
				}
			}
		);
	}
}

UCollectionObjective::UCollectionObjective()
{
	Type = EObjectiveType::Collect;
}

void UCollectionObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	TArray<AActor*> CollectableActors = QuestSubsystem->FindActorsOfClass(CollectableActorClass);

	for (int32 i = 0; i < CollectableActors.Num(); i++)
	{
		if (ICollectableObject* InteractTarget = Cast<ICollectableObject>(CollectableActors[i]))
		{
			InteractTarget->OnCollectionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
				{
					if (bCanBeCompleted && Instigator == InteractInstigator)
					{
						if (++CollectedCount >= TargetCount)
						{
							bIsCompleted = true;
							OnObjectiveCompleted.Broadcast(this);
							UE_LOG(LogTemp, Display, TEXT("CollectedCount %d, ProgressPercent 100%%"), CollectedCount);
							//CollectedCount = 0;
						}
						else
						{
							int32 ProgressPercent = CollectedCount * 100 / TargetCount;
							OnObjectiveInProgress.Broadcast(this, ProgressPercent);
							UE_LOG(LogTemp, Display, TEXT("CollectedCount %d, ProgressPercent %d%%"), CollectedCount, ProgressPercent);
						}
					}
				});
		}
	}

	/*if (auto* InteractTarget = Cast<ICollectableObject>(CollectObject))
	{
		InteractTarget->OnCollectionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			});
	}*/
}

UKillableObjective::UKillableObjective()
{
	Type = EObjectiveType::Kill;
}

void UKillableObjective::ActivateObjective(AActor* Instigator)
{
	Super::ActivateObjective(Instigator);

	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	TArray<AActor*> KillableActors = QuestSubsystem->FindActorsOfClass(KillableActorClass);

	for (int32 i = 0; i < KillableActors.Num(); i++)
	{
		if (IKillableObject* KillableTarget = Cast<IKillableObject>(KillableActors[i]))
		{
			KillableTarget->OnKillingFinished.AddLambda([this, Instigator](AActor* Object, AActor* KillableInstigator)
				{
					if (bCanBeCompleted && Instigator == KillableInstigator)
					{
						if (++KilledCount >= TargetCount)
						{
							bIsCompleted = true;
							OnObjectiveCompleted.Broadcast(this);
							UE_LOG(LogTemp, Display, TEXT("OnObjectiveCompleted"));
							UE_LOG(LogTemp, Display, TEXT("KilledCount %d, ProgressPercent 100%%"), KilledCount);
							//KilledCount = 0;
						}
						else
						{
							int32 ProgressPercent = KilledCount * 100 / TargetCount;
							OnObjectiveInProgress.Broadcast(this, ProgressPercent);
							UE_LOG(LogTemp, Display, TEXT("KilledCount %d, ProgressPercent %d%%"), KilledCount, ProgressPercent);
						}
					}
				});
		}
		else
		{
		}
	}
}