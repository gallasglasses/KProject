// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_CoreTypes.h"
#include "AI/KP_AIController.h"
#include "KP_AIFactory.generated.h"

class AAIController;
class UArrowComponent;
class UBoxComponent;

UCLASS()
class KPROJECT_API AKP_AIFactory : public AActor
{
	GENERATED_BODY()
	
public:	

	AKP_AIFactory();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Spawn Components")
		UArrowComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Components")
		UBoxComponent* FactoryBox;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Parametrs")
		TSubclassOf<AKP_AIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Parametrs")
		TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditAnywhere, Category = "Spawn Parametrs", meta = (ClampMin = "1", ClampMax = "1000.0")) //FGameData GameData;
		float AIPlayersNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parametrs")
		float SpawnRate = 1.0f;

private:

	void SpawnActors();
	void StartSpawnActorsTimer();

	FTimerHandle SpawnTimerHandle;
	int32 SpawnedActorsCount = 0;
};