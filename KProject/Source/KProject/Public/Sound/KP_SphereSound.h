// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_SphereSound.generated.h"

class USphereComponent;
class UAudioComponent;
class USoundCue;
class USoundAttenuation;

UCLASS()
class KPROJECT_API AKP_SphereSound : public AActor
{
	GENERATED_BODY()
	
public:	
	AKP_SphereSound();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
		USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
		USoundAttenuation* SoundAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
		float SphereRadius = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
		bool bIsRandomPlay = true;

	virtual void BeginPlay() override; 
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
