// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Objective.generated.h"

UENUM()
enum class EObjectiveType :uint8
{
	Location,
	Interact,
	Collect,
	Kill
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, UObjective*)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectiveInProgress, UObjective*, float /*ProgressPercent*/)

UCLASS(Abstract)
class QUESTSYSTEM_API UObjective : public UObject
{
	GENERATED_BODY()

public:
	virtual void ActivateObjective(AActor* Instigator) {};

	virtual FBox GetBoundingBox() const { return FBox(); }

	FName WorldTargetName = NAME_None;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		EObjectiveType Type;

	FOnObjectiveCompleted OnObjectiveCompleted;
	FOnObjectiveInProgress OnObjectiveInProgress;

	UPROPERTY(VisibleAnywhere)
		bool bIsCompleted;

	UPROPERTY(VisibleAnywhere)
		bool bCanBeCompleted;
};

UCLASS()
class QUESTSYSTEM_API UInteractionObjective : public UObjective
{
	GENERATED_BODY()
public:

	UInteractionObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual FBox GetBoundingBox() const override { return Target->GetComponentsBoundingBox(true); }

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "InteractableObject"))
		AActor* Target;

};

UCLASS()
class QUESTSYSTEM_API ULocationObjective : public UObjective
{
	GENERATED_BODY()
public:

	ULocationObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual FBox GetBoundingBox() const override { return Marker->GetComponentsBoundingBox(true); }

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "LocationMarker"))
		AActor* Marker;

};

UCLASS()
class QUESTSYSTEM_API UCollectionObjective : public UObjective
{
	GENERATED_BODY()

public:
	UCollectionObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> CollectableActorClass;

	UPROPERTY(EditAnywhere)
		int32 TargetCount = 0;

	UPROPERTY(VisibleAnywhere)
		int32 CollectedCount = 0;
};

UCLASS()
class QUESTSYSTEM_API UKillableObjective : public UObjective
{
	GENERATED_BODY()

public:
	UKillableObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> KillableActorClass;

	UPROPERTY(EditAnywhere)
		int32 TargetCount = 0;

	UPROPERTY(VisibleAnywhere)
		int32 KilledCount = 0;
};