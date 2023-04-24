// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup = "Collision", meta = (BlueprintSpawnableComponent, DisplayName = "Interaction Collision"))
class QUESTSYSTEM_API UInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InteractMessageWidget;

	UPROPERTY()
		UUserWidget* InteractMessage;

	UPROPERTY()
		AActor* ActorToInteract;

	UFUNCTION()
		void OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void Interact();

	private: 
		void HideInteractMessage();
};