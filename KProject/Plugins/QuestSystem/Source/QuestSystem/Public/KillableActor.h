// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "KillableObject.h"
#include "KillableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API AKillableActor : public AActor, public IKillableObject
{
	GENERATED_BODY()

public:

	AKillableActor();

	UFUNCTION(BlueprintCallable)
		void OnKillingFinished(AActor* ActorKilledObject);

	UFUNCTION()
		void OnDestroyKillableActor(AActor* Actor);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AKillableActor> KillableActorClass;
};