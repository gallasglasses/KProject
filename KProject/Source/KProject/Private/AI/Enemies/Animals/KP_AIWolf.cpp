// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/Animals/KP_AIWolf.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AKP_AIWolf::AKP_AIWolf(const FObjectInitializer& ObjInit) :Super(ObjInit)
{
	TriggerHitComponent->SetRelativeLocation(FVector(0.0f, 9.0f, 0.0f));
	TriggerHitComponent->SetBoxExtent(FVector(25.f, 15.f, 7.f));
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -99.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

