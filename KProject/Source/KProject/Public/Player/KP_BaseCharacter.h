// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "KP_CoreTypes.h"
#include "KP_BaseCharacter.generated.h"

class UKP_CharacterAbilitiesComponent;
class UKP_HealthComponent;
class UKP_StaminaComponent;
class UKP_ManaComponent;
class AKP_Shield;
class UInteractionComponent;
class UCollectionComponent;
class UKillingComponent;
class UQuestListComponent;
class UQuestList;

class UAnimMontage;
class UBoxComponent; 
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;

class UTextRenderComponent;
class UWidgetComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGiveAnyStaminaSignature, bool);
DECLARE_MULTICAST_DELEGATE(FOnGiveAnyManaSignature);
DECLARE_MULTICAST_DELEGATE(FDeadSignature);

UCLASS()
class KPROJECT_API AKP_BaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AKP_BaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_StaminaComponent* StaminaComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_ManaComponent* ManaComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* SwordTriggerHitComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_CharacterAbilitiesComponent* AbilitiesComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCollectionComponent* CollectionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UKillingComponent* KillingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UQuestListComponent* QuestListComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* LevelStartAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* BlockAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> RecoveryAnimMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AKP_Shield> ShieldClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(1000.f, 2000.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(VisibleAnywhere, Category = "Behavior Type")
	FGenericTeamId TeamID;

	UPROPERTY(EditAnywhere, Category = "Behavior Type")
	EBehaviorType InitialTeam = EBehaviorType::Neutral;
	
	virtual void BeginPlay() override;


	/*UFUNCTION(BlueprintCallable)
		void ToggleQuestListVisibility();*/

	UPROPERTY()
		UQuestList* QuestList;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UQuestList> QuestListClass;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsAttacking() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsBlocking() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsMoving() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float WeaponDamageAmount = 20.0f;

	UFUNCTION(BlueprintCallable, Category = "Behavior Type")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override { TeamID = NewTeamID; };

	UFUNCTION(BlueprintCallable, Category = "Behavior Type")
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

	void SetBlockingState(bool BlockingState);

	FOnGiveAnyStaminaSignature OnGiveAnyStamina;
	FOnGiveAnyManaSignature OnGiveAnyMana;
	FDeadSignature OnDead;

private:
	
	FTimerHandle AttackTimerHandle;
	FTimerHandle DeadTimerHandle;

	int8 ComboAttackCount = 0;
	int8 RecoveryCount = 0;

	float TimeAnimMontage = 0.0f;

	bool bWantsToRun = false;
	bool bIsRunning = false;
	bool bIsMoving = false;
	bool bIsAttacking = false;
	bool bIsDamageDone = false;
	bool bIsComboAttack = false;
	bool bIsBlocking = false;

	void Block();
	void ChooseComboAnimMontage();
	void ComboAttackSave();
	void ResetCombo();
	void OnDeath();
	void Dead();
	void OnExhausted();
	void OnMuggle();
	void OnHealthChanged(float Health, float HealthDelta);
	//void OnStaminaChanged(float Stamina, float StaminaDelta);
	void OnPlayAnimMontage(int8 Count);
	void OnStartAttacking();
	void OnStartRunning();
	void OnStopAttacking();
	void OnStopRunning();
	void MakeDamage(const FHitResult& HitResult);
	void MeleeAttack();
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	APlayerController* GetPlayerController() const;

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckCameraOverlap();
}; 
