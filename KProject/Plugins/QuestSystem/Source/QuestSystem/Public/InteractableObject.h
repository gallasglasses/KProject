// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObject.generated.h"


UINTERFACE(MinimalAPI)
class UInteractableObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinished, AActor* /*InteractableObject*/, AActor* /*ActorInteractedWithObject*/);

class QUESTSYSTEM_API IInteractableObject
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be 
		//inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Interact(AActor* ActorInteractedWithObject);

	UFUNCTION()
		virtual void Interact_Implementation(AActor* ActorInteractedWithObject) {};

	UFUNCTION()
	virtual void NotifyInteractionFinished(AActor* InteractableObject, AActor* ActorInteractedWithObject);

	FOnInteractionFinished OnInteractionFinished;
};