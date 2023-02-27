// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KP_WeaponComponent.generated.h"

class AKP_Dagger;

DECLARE_MULTICAST_DELEGATE(FOnWantToStartThrowingSignature);
DECLARE_MULTICAST_DELEGATE(FOnWantToStopThrowingSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KPROJECT_API UKP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UKP_WeaponComponent();

	FOnWantToStartThrowingSignature OnWantToStartThrowing;
	FOnWantToStopThrowingSignature OnWantToStopThrowing;

	void OnWantToStart();
	void OnWantToStop();
	void ThrowDagger();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AKP_Dagger> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = "FX_Dagger";

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AKP_Dagger* Weapon = nullptr;

	void SpawnWeapon();
		
};
