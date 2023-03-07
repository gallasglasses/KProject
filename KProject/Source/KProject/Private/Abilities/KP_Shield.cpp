// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/KP_Shield.h"
#include "Weapons/KP_DaggerProjectile.h"
#include "Weapons/KP_Projectile.h"
#include "Player/KP_BaseCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(ShieldLog, All, All);

AKP_Shield::AKP_Shield()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(15.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>("ShieldMesh");
	ShieldMesh->SetRelativeScale3D(FVector(15.f, 15.f, 15.f));
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ShieldMesh->SetupAttachment(GetRootComponent());
}

void AKP_Shield::BeginPlay()
{
	Super::BeginPlay();
	
	SetDefenseAmount(MaxDefenseAmount);
	GetWorld()->GetTimerManager().SetTimer(ShieldLifeTimerHandle, this, &AKP_Shield::DestroyShield, LifeSeconds, false);

	const auto ComponentOwner = Cast<AKP_BaseCharacter>(GetOwner());
	if (ComponentOwner->IsBlocking())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &AKP_Shield::OnTakeAnyDamage);

		UE_LOG(ShieldLog, Display, TEXT("OnTakeAnyDamage shield"));
	}
}

void AKP_Shield::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Projectile = Cast<AKP_Projectile>(OtherActor);
	if (Projectile)
	{
		UE_LOG(ShieldLog, Display, TEXT("Projectile on shield"));
	}
}

void AKP_Shield::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || !IsShieldActive() || !GetWorld()) return;

	SetDefenseAmount(DefenseAmount - Damage);
	//DamageCauser->Destroy();
	if (!IsShieldActive())
	{
		DestroyShield();
	}
}

void AKP_Shield::SetDefenseAmount(float NewDefenseAmount)
{
	const auto NextDefenseAmount = FMath::Clamp(NewDefenseAmount, 0.0f, MaxDefenseAmount);

	UE_LOG(ShieldLog, Display, TEXT("NextDefenseAmount %f"), NextDefenseAmount);
	DefenseAmount = NextDefenseAmount;
}

void AKP_Shield::DestroyShield()
{
	if (IsShieldActive())
	{
		SetDefenseAmount(0.f);
	}

	GetWorld()->GetTimerManager().ClearTimer(ShieldLifeTimerHandle);
	UE_LOG(ShieldLog, Display, TEXT("Destroy Shield"));
	const auto ShieldOwner = Cast<AKP_BaseCharacter>(GetOwner());
	if (!ShieldOwner) return;
	ShieldOwner->SetBlockingState(IsShieldActive());
	Destroy();
}