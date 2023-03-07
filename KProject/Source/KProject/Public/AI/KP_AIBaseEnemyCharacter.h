// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KP_AIBaseEnemyCharacter.generated.h"

class UKP_HealthComponent;
class UKP_StaminaComponent;
class UKP_ManaComponent;
class UKP_WeaponComponent;
class UAnimMontage;
class UBehaviorTree;
class UBoxComponent;

class UWidgetComponent;

UCLASS()
class KPROJECT_API AKP_AIBaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AKP_AIBaseEnemyCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BehaviorTree")
		UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		bool HasSpawnWeapon = true;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsAttacking() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	void OnStartAttacking();
	void OnStopAttacking();

	bool CanAttack() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UKP_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UKP_WeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
		bool HasAnimMontage = true;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (EditCondition = "HasAnimMontage"))
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (EditCondition = "HasAnimMontage"))
		UAnimMontage* LevelStartAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (EditCondition = "HasAnimMontage"))
		TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(1000.f, 2000.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (EditCondition = "!HasSpawnWeapon"))
		float DamageAmount = 1.0f;

	/*You need to check this value in BehaviorTree for this actor in service IsPlayerInRange. The value must be the same.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (EditCondition = "!HasSpawnWeapon"))
		float AttackRange = 0.f;

	virtual void BeginPlay() override;

	virtual void OnDeath();

	bool bIsAttacking = false;
	bool bIsDamageDone = false;
	bool bIsInRange = false;


private:

	FTimerHandle AttackTimerHandle;

	int8 ComboAttackCount = 0;

	FVector EnemyLocation;

	float TimeAnimMontage = 0.0f;

	bool bIsComboAttack = false;
	bool bWantsToRun = false;
	bool bIsRunning = false;

	void Block();
	void ChooseComboAnimMontage();
	void ComboAttackSave();
	void ResetCombo();
	void OnHealthChanged(float Health, float HealthDelta);
	void OnPlayAnimMontage(int8 Count);
	void StopAttack();
	virtual void MeleeAttack();
	virtual void Attacking();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
