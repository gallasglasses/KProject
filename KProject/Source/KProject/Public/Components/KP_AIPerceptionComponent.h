// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "KP_AIPerceptionComponent.generated.h"

UCLASS()
class KPROJECT_API UKP_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	
	AActor* GetClosetEnemy() const;
};
