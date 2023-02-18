// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KP_BaseCharacter.generated.h"

class UCameraComponent;
class UKP_HealthComponent;
class USpringArmComponent;
class UAnimMontage;

class UTextRenderComponent;

UCLASS()
class KPROJECT_API AKP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKP_BaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* LevelStartAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(1000.f, 2000.f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10.f, 100.f);
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

private:

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnStopRunning();
	void Fight();
	void Block();
	void OnDeath();
	void OnHealthChanged(float Health);

	bool bWantsToRun = false;

	
};
