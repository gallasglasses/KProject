// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/KP_DaggerProjectile.h"
#include "Components/KP_PhysicsMovementComponent.h"
#include "AI/KP_AIController.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(DaggerProjectileLog, All, All);

AKP_DaggerProjectile::AKP_DaggerProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->SetBoxExtent(FVector(18.0f, 1.3f, 3.3f));

	DaggerMesh = CreateDefaultSubobject<UStaticMeshComponent>("DaggerMesh");
	DaggerMesh->SetupAttachment(CollisionComponent);
	DaggerMesh->SetRelativeLocation(FVector(-35.f, 0.f, 1.5f));
	DaggerMesh->SetRelativeRotation(FRotator(90.0f, 0.f, 0.f));

	/*MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("DaggerMovementComponent");
	MovementComponent->InitialSpeed = 2.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;*/

	MovementComponent = CreateDefaultSubobject<UKP_PhysicsMovementComponent>("DaggerPhysicsMovementComponent");
}

void AKP_DaggerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Without physic
	/*FVector NextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(NextPosition, true);*/

	if (FVector::Dist(GetActorLocation(), StartPosition) > FireRange)
	{
		Stop();
	}
}

void AKP_DaggerProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(CollisionComponent);

	CollisionComponent->SetRelativeRotation((CollisionComponent->GetRelativeRotation()) + ActorRotator);

	StartPosition = GetActorLocation();//

	//MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	MovementComponent->Velocity = GetActorForwardVector() * MoveSpeed;
	MovementComponent->SetComponentTickEnabled(true);

	//UE_LOG(DaggerProjectileLog, Display, TEXT("Velocity: %s"), *MovementComponent->Velocity.ToString());

	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	//UE_LOG(DaggerProjectileLog, Display, TEXT("Owner: %s"), GetOwner());

	CollisionComponent->OnComponentHit.AddDynamic(this, &AKP_DaggerProjectile::OnProjectileHit);

	SetLifeSpan(LifeSeconds);
}

void AKP_DaggerProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	Stop();
	const auto KP_AIController = Cast<AKP_AIController>(GetController());
	if (KP_AIController && KP_AIController->GetTeamAttitudeTowards(*OtherActor) == ETeamAttitude::Hostile)
	{
		UE_LOG(DaggerProjectileLog, Display, TEXT("Hostile"));
	
		UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, ShotDirection, Hit, GetController(), this, UDamageType::StaticClass());
		//DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 24.f, FColor::Magenta, false, 5.0f);
	}
	else
	{
		UE_LOG(DaggerProjectileLog, Display, TEXT("Friendly"));
	}
	Destroy();
}

AController* AKP_DaggerProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void AKP_DaggerProjectile::Stop()
{
	MovementComponent->Velocity = FVector::ZeroVector;
	MovementComponent->SetComponentTickEnabled(false);
	PrimaryActorTick.SetTickFunctionEnable(false);
	DaggerMesh->SetHiddenInGame(true);
	DaggerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}