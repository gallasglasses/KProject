// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableObject.h"
#include "KP_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class KPROJECT_API AKP_AICharacter : public ACharacter, public IInteractableObject
{
	GENERATED_BODY()

public:
	
	AKP_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTreeAsset;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable)
		void OnInteractionFinished(AActor* ActorInteractedWithObject);

};
