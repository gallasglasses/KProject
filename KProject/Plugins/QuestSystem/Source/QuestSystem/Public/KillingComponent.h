// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "KillingComponent.generated.h"


UCLASS( ClassGroup= "Collision", meta=(BlueprintSpawnableComponent, DisplayName = "Killing Collision") )
class QUESTSYSTEM_API UKillingComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	
	UKillingComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		AActor* ActorToKill;

	UFUNCTION()
		void OnKillingCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnKillingCompEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void Kill();
		
};
