// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestList.h"
#include "Quest.h"
#include "QuestDescription.h"
#include "QuestListComponent.h"
#include "QuestListEntry.h"
#include "Components/ScrollBox.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UQuestList::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UnpauseButton)
	{
		UnpauseButton->OnClicked.AddDynamic(this, &UQuestList::OnUnpause);
	}
}

void UQuestList::OnUnpause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UQuestList::Init(UQuestListComponent* QuestList)
{
	UE_LOG(LogTemp, Display, TEXT("UQuestList::Init"));
	if (QuestList && QuestEntryClass)
	{
		for (AQuest* Quest : QuestList->GetQuests())
		{
			if (Quest->IsCompleted())
			{
				OnActiveQuestChanged(Quest);
				continue;
			}
			UScrollBox* Scroll = Quest->bIsStoryQuest ? StoryQuestsList : SideQuestsList;

			if (Scroll)
			{
				UQuestListEntry* QuestEntry = CreateWidget<UQuestListEntry>(this, QuestEntryClass);
				QuestEntry->SetQuestText(Quest->Name);
				QuestEntry->OnQuestChosen.BindUObject(QuestList, &UQuestListComponent::SetActiveQuest, Quest);
				QuestEntries.Add(Quest, QuestEntry);
				Scroll->AddChild(QuestEntry);
			}
		}
		OnActiveQuestChanged(QuestList->GetActiveQuest());
		QuestList->OnActiveQuestChanged.AddUObject(this, &UQuestList::OnActiveQuestChanged);

		
	}
}

void UQuestList::OnActiveQuestChanged(AQuest* ActiveQuest)
{
	for (const TPair<AQuest*, UQuestListEntry*>& Pair : QuestEntries)
	{
		Pair.Value->SetIsSelected(Pair.Key == ActiveQuest);
	}
	if (ActiveQuestDescription)
	{
		ActiveQuestDescription->Init(ActiveQuest);
		ActiveQuestDescription->SetVisibility(ActiveQuest ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}