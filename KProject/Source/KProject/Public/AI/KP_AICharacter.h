// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KP_AICharacter.generated.h"

class UKP_HealthComponent;
class UKP_StaminaComponent;
class UKP_ManaComponent;
class UKP_WeaponComponent;
class UAnimMontage;
class UCameraComponent;
class USpringArmComponent;
class UBehaviorTree;

class UTextRenderComponent;
class UWidgetComponent;

UCLASS()
class KPROJECT_API AKP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AKP_AICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTreeAsset;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UKP_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UKP_WeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		UAnimMontage* LevelStartAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
		TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamageVelocity = FVector2D(1000.f, 2000.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FVector2D LandedDamage = FVector2D(10.f, 100.f);

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsAttacking() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsThrowingWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetThrowing(bool bIsActing);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float WeaponDamageAmount = 10.0f;

	void OnStartAttacking();
	void OnStopAttacking();


private:

	FTimerHandle AttackTimerHandle;

	int8 ComboAttackCount = 0;

	FVector EnemyLocation;

	float TimeAnimMontage = 0.0f;

	bool bIsAttacking = false;
	bool bIsThrowingWeapon = false;
	bool bIsDamageDone = false;
	bool bIsComboAttack = false;

	void Block();
	void ChooseComboAnimMontage();
	void ComboAttackSave();
	void ResetCombo();
	void OnDeath();
	void OnHealthChanged(float Health, float HealthDelta);
	void OnPlayAnimMontage(int8 Count);
	void StopAttack();
	void MeleeAttack();
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);
};
