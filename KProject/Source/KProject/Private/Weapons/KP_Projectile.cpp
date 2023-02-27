// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/KP_Projectile.h"
//
//#include "Components/SphereComponent.h"

AKP_Projectile::AKP_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;/*
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.f);
	SetRootComponent(CollisionComponent);*/
}

void AKP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}
