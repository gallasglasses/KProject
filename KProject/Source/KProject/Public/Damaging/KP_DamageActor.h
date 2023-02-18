// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_DamageActor.generated.h"

UCLASS()
class KPROJECT_API AKP_DamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKP_DamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
