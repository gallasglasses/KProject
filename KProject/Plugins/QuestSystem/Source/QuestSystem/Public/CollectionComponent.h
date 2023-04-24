// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CollectionComponent.generated.h"

UCLASS(ClassGroup = "Collision", meta = (BlueprintSpawnableComponent, DisplayName = "Collection Collision"))
class QUESTSYSTEM_API UCollectionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UCollectionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CollectMessageWidget;

	UPROPERTY()
		UUserWidget* CollectMessage;

	UPROPERTY()
		AActor* ActorToCollect;

	UFUNCTION()
		void OnCollectionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnCollectionCompEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void Collect();
};