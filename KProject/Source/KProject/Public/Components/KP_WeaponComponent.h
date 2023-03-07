// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KP_WeaponComponent.generated.h"

class AKP_Dagger;

DECLARE_MULTICAST_DELEGATE(FOnWantToStartAttackSignature);
DECLARE_MULTICAST_DELEGATE(FOnWantToStopAttackSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KPROJECT_API UKP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UKP_WeaponComponent();

	FOnWantToStartAttackSignature OnWantToStartAttack;
	FOnWantToStopAttackSignature OnWantToStopAttack;

	void OnWantToStart();
	void OnWantToStop();
	void WeaponAttack();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AKP_Dagger> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = "FX_Dagger";

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY()
	AKP_Dagger* Weapon = nullptr;

	void SpawnWeapon();
};
