// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableObject.h"
#include "QuestSystemCharacter.generated.h"

class UQuestList;
class UQuestDialog;
class UQuestListComponent;
class AQuest;

UCLASS()
class QUESTSYSTEM_API AQuestSystemCharacter : public ACharacter, public IInteractableObject
{
	GENERATED_BODY()

public:
	AQuestSystemCharacter();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UQuestListComponent* QuestListComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestStatus")
		UStaticMeshComponent* NewQuestStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestStatus")
		UStaticMeshComponent* AcceptedQuestStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestStatus")
		UStaticMeshComponent* CompletedQuestStatus;

	void AssignedStatusQuest(AQuest* CurrentQuest);
public:

	virtual void Interact_Implementation(AActor* InteractInstigator) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UQuestDialog> QuestDialogClass;
};