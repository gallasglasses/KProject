// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/KP_BasePickup.h"

#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BasePickupLog, All, All);

AKP_BasePickup::AKP_BasePickup()
{

	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

}

void AKP_BasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
}

void AKP_BasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

void AKP_BasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AKP_BasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AKP_BasePickup::PickupWasTaken()
{
	Destroy();
	UE_LOG(BasePickupLog, Display, TEXT("Pickup was destroy"));

	/*CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AKP_BasePickup::Respawn, RespawnTime);*/
}

//void AKP_BasePickup::Respawn()
//{
//	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
//	if (GetRootComponent())
//	{
//		GetRootComponent()->SetVisibility(true, true);
//	}
//}