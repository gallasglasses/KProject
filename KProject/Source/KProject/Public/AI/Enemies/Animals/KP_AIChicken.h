// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/Animals/KP_AIEnemyAnimals.h"
#include "KP_AIChicken.generated.h"

class UBoxComponent;

UCLASS()
class KPROJECT_API AKP_AIChicken : public AKP_AIEnemyAnimals
{
	GENERATED_BODY()
	
public:

	AKP_AIChicken(const FObjectInitializer& ObjInit);

private:

	virtual void MeleeAttack() override;
};
