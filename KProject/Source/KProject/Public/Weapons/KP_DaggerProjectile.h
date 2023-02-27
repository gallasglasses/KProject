// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/KP_Projectile.h"
#include "KP_DaggerProjectile.generated.h"

class UBoxComponent;
//class UProjectileMovementComponent;
class UKP_PhysicsMovementComponent;
class UStaticMeshComponent;

UCLASS()
class KPROJECT_API AKP_DaggerProjectile : public AKP_Projectile
{
	GENERATED_BODY()

public:

	AKP_DaggerProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
	void SetActorRotator(const FRotator& Rotator) { ActorRotator = Rotator; }

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* DaggerMesh;

	/*UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UProjectileMovementComponent* MovementComponent;*/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UKP_PhysicsMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Fire Parametrs")
		float DamageAmount = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Fire Parametrs")
		float LifeSeconds = 5.0f; 
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Fire Parametrs")
		float MoveSpeed = 100.0f; 
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Fire Parametrs")
		float FireRange = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Fire Parametrs")
		float Mass = 10.0f;

	virtual void BeginPlay() override;

private:

	FVector ShotDirection;
	FRotator ActorRotator;
	FVector StartPosition;

	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Stop();

	AController* GetController() const;
	
};
