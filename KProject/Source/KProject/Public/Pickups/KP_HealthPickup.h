// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KP_BasePickup.h"
#include "KP_HealthPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class KPROJECT_API AKP_HealthPickup : public AKP_BasePickup
{
	GENERATED_BODY()

public:
	AKP_HealthPickup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float HealthAmount = 50.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
