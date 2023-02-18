// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KP_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KPROJECT_API UKP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UKP_HealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.f;

private:

	FTimerHandle HealTimerHandle;
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
	void HealUpdate();
	void SetHealth(float NewHealth);
};
