// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_BasePickup.generated.h"

class USphereComponent;

UCLASS()
class KPROJECT_API AKP_BasePickup : public AActor
{
	GENERATED_BODY()
	
public:	

	AKP_BasePickup();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.f;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	

	virtual void Tick(float DeltaTime) override;

private:
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
	//void Respawn();

};
