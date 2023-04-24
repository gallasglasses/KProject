// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KillableObject.generated.h"


UINTERFACE(MinimalAPI)
class UKillableObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnKillingFinished, AActor* /*KillableObject*/, AActor* /*ActorKilledObject*/);

class QUESTSYSTEM_API IKillableObject
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be 
		//inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Kill(AActor* ActorKilledObject);

	UFUNCTION()
		virtual void Kill_Implementation(AActor* ActorKilledObject) {};

	virtual void NotifyKillingFinished(AActor* KillableObject, AActor* ActorKilledObject);

	FOnKillingFinished OnKillingFinished;
};