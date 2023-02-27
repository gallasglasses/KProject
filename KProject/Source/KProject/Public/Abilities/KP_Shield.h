// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/KP_Ability.h"
#include "KP_Shield.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class KPROJECT_API AKP_Shield : public AKP_Ability
{
	GENERATED_BODY()
	
public:	

	AKP_Shield();

	UFUNCTION(BlueprintCallable, Category = "Shield Parametrs")
	bool IsShieldActive() const { return !(FMath::IsNearlyZero(DefenseAmount)); }

	void SetDefenseAmount(float NewDefenseAmount);

	float GetTransmittedDamagePercent() const { return TransmittedDamagePercent; };

protected:

	virtual void BeginPlay() override; 
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ShieldMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shield Parametrs", meta = (ClampMin = "0", ClampMax = "100.0"))
	float LifeSeconds = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shield Parametrs", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxDefenseAmount = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shield Parametrs")
	float TransmittedDamagePercent = 0.05f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:	

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle ShieldLifeTimerHandle;
	float DefenseAmount = 0.0f;

	void DestroyShield();

	bool bIsDamageDone = false;

};
