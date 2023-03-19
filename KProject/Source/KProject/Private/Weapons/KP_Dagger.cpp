// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/KP_Dagger.h"
#include "Weapons/KP_DaggerProjectile.h"
#include "AI/KP_AIBaseEnemyCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(DaggerLog, All, All);

AKP_Dagger::AKP_Dagger()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AKP_Dagger::OnStart()
{
    UE_LOG(DaggerLog, Display, TEXT("Throw!"));

    MakeShot();
}

void AKP_Dagger::OnStop()
{

}

void AKP_Dagger::BeginPlay()
{
	Super::BeginPlay();

    check(WeaponMesh);
}

void AKP_Dagger::MakeShot()
{
    if (!GetWorld())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        UE_LOG(DaggerLog, Display, TEXT("GetTraceData FALSE"));
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint + GetMuzzleWorldLocation().GetSafeNormal());

    //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Magenta, false, 1.f, 0, 3.f);
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AKP_DaggerProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKP_DaggerProjectile>(DaggerProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetActorRotator(GetPlayer()->GetActorRotation());//
        UE_LOG(DaggerLog, Display, TEXT("Direction: %s"), *Direction.ToString());

        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    } 
    else 
    {
        UE_LOG(DaggerLog, Display, TEXT("Projectile NULL"));
        return;
    }
}

bool AKP_Dagger::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    UE_LOG(DaggerLog, Display, TEXT("GetTraceData"));
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    {
        UE_LOG(DaggerLog, Display, TEXT("GetPlayerViewPoint FALSE"));
        return false;
    }

    TraceStart = ViewLocation;

    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    UE_LOG(DaggerLog, Display, TEXT("TraceEnd %s"), *TraceEnd.ToString());

    return true;
}

FVector AKP_Dagger::GetMuzzleWorldLocation() const
{
    UE_LOG(DaggerLog, Display, TEXT("GetMuzzleWorldLocation %s"), *(WeaponMesh->GetSocketLocation(WeaponSocketName)).ToString());
    return WeaponMesh->GetSocketLocation(WeaponSocketName);
}

void AKP_Dagger::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
    UE_LOG(DaggerLog, Display, TEXT("MakeHit"));
}

void AKP_Dagger::MakeDamage(FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), GetPlayer());
}

ACharacter* AKP_Dagger::GetPlayer() const
{
	return !Cast<ACharacter>(GetOwner()) ? nullptr : Cast<ACharacter>(GetOwner());
}

//APlayerController* AKP_Dagger::GetPlayerController() const
//{
//    return !GetPlayer() ? nullptr : GetPlayer()->GetController<APlayerController>();
//}

AController* AKP_Dagger::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

bool AKP_Dagger::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto KP_Character = Cast<ACharacter>(GetOwner());
    if(!KP_Character) return false;
    if (KP_Character->IsPlayerControlled())
    {
        UE_LOG(DaggerLog, Display, TEXT("PlayerControlled"));
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = KP_Character->GetActorRotation(); 
        UE_LOG(DaggerLog, Display, TEXT("GetPlayerViewPoint AI"));
    }

	return true;
}
