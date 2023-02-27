// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_Projectile.generated.h"

//class USphereComponent;

UCLASS()
class KPROJECT_API AKP_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AKP_Projectile();

protected:

	/*UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;*/

	virtual void BeginPlay() override;
};
