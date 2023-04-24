// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestSystemCharacter.h"
#include "Quest.h"
#include "QuestListComponent.h"
#include "QuestList.h"
#include "QuestDialog.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AQuestSystemCharacter::AQuestSystemCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	QuestListComponent = CreateDefaultSubobject<UQuestListComponent>(TEXT("QuestListComponent"));

	//FAttachmentTransformRules EquipAttachmentRules(EAttachmentRule::KeepRelative, false);

	NewQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("NewQuestStatus");
	NewQuestStatus->SetupAttachment(GetRootComponent());
	//NewQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//NewQuestStatus->SetHiddenInGame(true);

	AcceptedQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("AcceptedQuestStatus");
	AcceptedQuestStatus->SetupAttachment(GetRootComponent());
	//AcceptedQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//AcceptedQuestStatus->SetHiddenInGame(true);

	CompletedQuestStatus = CreateDefaultSubobject<UStaticMeshComponent>("CompletedQuestStatus");
	CompletedQuestStatus->SetupAttachment(GetRootComponent());
	//CompletedQuestStatus->AttachToComponent(GetMesh(), EquipAttachmentRules, "QuestStatus");
	//CompletedQuestStatus->SetHiddenInGame(true);
}

void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (auto& Actor : AttachedActors)
	{
		AQuest* CheckedQuest = Cast<AQuest>(Actor);
		if (CheckedQuest == nullptr)
		{
			continue;
		}
		else
		{
			CheckedQuest->OnStatusChanged.AddUObject(this, &AQuestSystemCharacter::AssignedStatusQuest);
		}
	}

}

void AQuestSystemCharacter::AssignedStatusQuest(AQuest* CurrentQuest)
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	TArray<AQuest*> CheckedQuests;
	for (auto& Actor : AttachedActors)
	{
		if (Cast<AQuest>(Actor))
		{
			CheckedQuests.Add(Cast<AQuest>(Actor));
		}
	}	
	int32 Index;
	if(CheckedQuests.Find(CurrentQuest, Index)) // && CheckedQuests.IsValidIndex(Index + 1)
	{
		if (!CheckedQuests[Index]->bIsTaken && !CheckedQuests[Index]->IsCompleted() && CheckedQuests[Index]->IsAvailable())
		{
			UE_LOG(LogTemp, Display, TEXT("NewQuestStatus"));
			NewQuestStatus->SetHiddenInGame(false);
			AcceptedQuestStatus->SetHiddenInGame(true);
			CompletedQuestStatus->SetHiddenInGame(true);
		}
		else if (CheckedQuests[Index]->bIsTaken && !CheckedQuests[Index]->IsCompleted())
		{
			UE_LOG(LogTemp, Display, TEXT("AcceptedQuestStatus"));
			NewQuestStatus->SetHiddenInGame(true);
			AcceptedQuestStatus->SetHiddenInGame(false);
			CompletedQuestStatus->SetHiddenInGame(true);
		}
		else if (CheckedQuests.IsValidIndex(Index + 1))
		{
			if (CheckedQuests[Index]->IsCompleted() && CheckedQuests[Index + 1]->IsAvailable() && !CheckedQuests[Index + 1]->bIsTaken && !CheckedQuests[Index + 1]->IsCompleted())
			{
				UE_LOG(LogTemp, Display, TEXT("NextQuestStatus"));
				NewQuestStatus->SetHiddenInGame(false);
				AcceptedQuestStatus->SetHiddenInGame(true);
				CompletedQuestStatus->SetHiddenInGame(true);
			}
		}
		else if (CheckedQuests[Index] == CheckedQuests.Last() && CheckedQuests[Index]->IsCompleted())
		{
			UE_LOG(LogTemp, Display, TEXT("AllQuestsCompleted"));
			NewQuestStatus->SetHiddenInGame(true);
			AcceptedQuestStatus->SetHiddenInGame(true);
			CompletedQuestStatus->SetHiddenInGame(true);
		}
		else 
		{
			UE_LOG(LogTemp, Display, TEXT("CompletedQuestStatus"));
			NewQuestStatus->SetHiddenInGame(true);
			AcceptedQuestStatus->SetHiddenInGame(true);
			CompletedQuestStatus->SetHiddenInGame(false);
		}
	}
}

void AQuestSystemCharacter::Interact_Implementation(AActor* InteractInstigator)
{
	if (InteractInstigator == nullptr)
	{
		return;
	}

	UActorComponent* ActorQuestListComp = InteractInstigator->GetComponentByClass(UQuestListComponent::StaticClass());

	if (ActorQuestListComp)
	{
		UQuestListComponent* ActorQuestList = Cast<UQuestListComponent>(ActorQuestListComp);

		UE_LOG(LogTemp, Display, TEXT("Interact_Implementation start"));

		TArray<AActor*> AttachedActors;
		GetAttachedActors(AttachedActors);

		bool bHadQuestsAvailable = false;

		for (auto& Actor : AttachedActors)
		{
			AQuest* Quest = Cast<AQuest>(Actor);
			if (Quest == nullptr)
			{
				continue;
			}

			if (Quest->bIsTaken && Quest->IsCompleted() || (Quest->PreviousQuest && !Quest->PreviousQuest->IsCompleted()))
			{
				continue;
			}

			if (QuestDialogClass)
			{
				UQuestDialog* QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
				UE_LOG(LogTemp, Display, TEXT("QuestDialog start"));

				QuestDialog->Init(Quest);
				QuestDialog->OnQuestAccepted.BindUObject(ActorQuestList, &UQuestListComponent::AddQuest, Quest);
				QuestDialog->OnDialogExit.BindLambda([this, InteractInstigator]()
					{
						NotifyInteractionFinished(this, InteractInstigator);
					});
				QuestDialog->AddToViewport();
				return;
			}
			bHadQuestsAvailable = true;
		}
		if (!bHadQuestsAvailable)
		{
			NotifyInteractionFinished(this, InteractInstigator);
		}
	}

}