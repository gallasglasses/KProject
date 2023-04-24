// Fill out your copyright notice in the Description page of Project Settings.

#include "CurrentObjectives.h"
#include "Quest.h"
#include "ObjectiveWidget.h"
#include "Components/VerticalBox.h"

void UCurrentObjectives::SetCurrentObjectives(AQuest* Quest)
{
	if (ObjectivesList && ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		if (!Quest->IsCompleted())
		{
			for (UObjective* Objective : Quest->GetObjectives())
			{
				UObjectiveWidget* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
				ObjectiveWidget->Init(Objective);
				ObjectivesList->AddChildToVerticalBox(ObjectiveWidget);
			}
		}
	}
}