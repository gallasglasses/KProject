// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestList.generated.h"

class UQuestListComponent;
class UScrollBox;
class UQuestDescription;
class AQuest;
class UQuestListEntry;
class UTextBlock;
class UButton;


UCLASS()
class QUESTSYSTEM_API UQuestList : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UQuestListComponent* QuestList);

protected:

	UPROPERTY(meta = (BindWidgetOptional))
		UScrollBox* StoryQuestsList;

	UPROPERTY(meta = (BindWidgetOptional))
		UScrollBox* SideQuestsList;

	UPROPERTY(meta = (BindWidgetOptional))
		UQuestDescription* ActiveQuestDescription;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UQuestListEntry> QuestEntryClass;

	UPROPERTY()
		TMap<AQuest*, UQuestListEntry*> QuestEntries;

	void OnActiveQuestChanged(AQuest* ActiveQuest);	
	
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* UnpauseButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* UnpauseButtonText;

private:

	UFUNCTION()
		void OnUnpause();
};