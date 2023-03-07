// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "KP_AIEnemyAnimals.generated.h"

class UBoxComponent;

UCLASS()
class KPROJECT_API AKP_AIEnemyAnimals : public AKP_AIBaseEnemyCharacter
{
	GENERATED_BODY()

public:

	AKP_AIEnemyAnimals(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerHitComponent;

private:

	void MakeDamage(const FHitResult& HitResult);

	APlayerController* GetPlayerController() const;

	UFUNCTION()
		void OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
