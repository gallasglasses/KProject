// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestListComponent.generated.h"

class AQuest;
class UCurrentObjectives;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuest*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UQuestListComponent();

protected:

	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddQuest(AQuest* Quest);

	const TArray<AQuest*>& GetQuests() const;

	UFUNCTION(BlueprintCallable, Category = "QuestListComponent")
	TArray<AActor*> GetInteractableQuestsObjects();

	UFUNCTION(BlueprintCallable, Category = "QuestListComponent")
	AQuest* GetActiveQuest() const;

	void SetActiveQuest(AQuest* Quest);

	//UPROPERTY(BlueprintAssignable)
	FOnQuestAction OnActiveQuestChanged;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCurrentObjectives> CurrentObjectivesWidget;

private:

	UPROPERTY()
		TArray<AQuest*> AcceptedQuests;

	UPROPERTY()
		AQuest* ActiveQuest;
};