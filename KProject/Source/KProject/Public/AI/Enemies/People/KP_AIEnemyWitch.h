// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "KP_AIEnemyWitch.generated.h"

class UKP_WeaponComponent;

UCLASS()
class KPROJECT_API AKP_AIEnemyWitch : public AKP_AIBaseEnemyCharacter
{
	GENERATED_BODY()

public:

	AKP_AIEnemyWitch(const FObjectInitializer& ObjInit);

protected:

public:

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsThrowingWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetThrowing(bool bIsActing);

private:

	bool bIsThrowingWeapon = false;
};
