// Fill out your copyright notice in the Description page of Project Settings.


#include "Damaging/KP_DamageActor.h"
//#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AKP_DamageActor::AKP_DamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void AKP_DamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKP_DamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

