// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectableObject.generated.h"


UINTERFACE(MinimalAPI)
class UCollectableObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCollectionFinished, AActor* /*CollectableObject*/, AActor* /*ActorCollectedObject*/);

class QUESTSYSTEM_API ICollectableObject
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be 
		//inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Collect(AActor* ActorCollectedObject);

	UFUNCTION()
		virtual void Collect_Implementation(AActor* ActorCollectedObject) {};

	virtual void NotifyCollectionFinished(AActor* CollectableObject, AActor* ActorCollectedObject);

	FOnCollectionFinished OnCollectionFinished;
};