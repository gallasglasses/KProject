// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_Dagger.generated.h"

class AKP_DaggerProjectile;
class USkeletalMeshComponent;

UCLASS()
class KPROJECT_API AKP_Dagger : public AActor
{
	GENERATED_BODY()
	
public:	

	AKP_Dagger();

	void OnStart();
	void OnStop();
	
protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
        USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
        FName WeaponSocketName = "SM_DaggerWeaponSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
        TSubclassOf<AKP_DaggerProjectile> DaggerProjectileClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
        float TraceMaxDistance = 1500.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
        float DamageAmount = 10.0f;

    void BeginPlay();
    void MakeShot();

    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(FHitResult& HitResult);

    ACharacter* GetPlayer() const;
    APlayerController* GetPlayerController() const;


    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
};
