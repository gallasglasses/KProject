// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestDescription.generated.h"

class UObjectiveWidget;
class AQuest;
class UTextBlock;
class UScrollBox;

UCLASS()
class QUESTSYSTEM_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
		UScrollBox* ObjectivesList;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DescriptionText;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

public:

	void Init(AQuest* Quest);
};