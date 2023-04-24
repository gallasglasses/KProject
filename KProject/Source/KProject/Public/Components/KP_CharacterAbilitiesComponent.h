// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KP_CharacterAbilitiesComponent.generated.h"

class AKP_Shield;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KPROJECT_API UKP_CharacterAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UKP_CharacterAbilitiesComponent();

	AKP_Shield* GetShield() const { return Shield; };

	void SpawnAbility();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
		TSubclassOf<AKP_Shield> AbilityClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
		FName AbilitySocketName = "spine_01";

	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		AKP_Shield* Shield = nullptr;

	virtual void BeginPlay() override;

private:

};
