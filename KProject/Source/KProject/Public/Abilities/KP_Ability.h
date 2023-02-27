// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_Ability.generated.h"

UCLASS()
class KPROJECT_API AKP_Ability : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AKP_Ability();

protected:
	
	virtual void BeginPlay() override;

};
