// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/Animals/KP_AIChicken.h"

#include "QuestSubsystem.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AIChickenLog, All, All);

AKP_AIChicken::AKP_AIChicken(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	TriggerHitComponent->SetRelativeLocation(FVector(10.0f, 0.0f, 23.0f));
	TriggerHitComponent->SetBoxExtent(FVector(5.f, 1.f, 1.f));
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCapsuleRadius(10.f);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));

}

void AKP_AIChicken::MeleeAttack()
{
	bIsAttacking = true;
	//UE_LOG(AIChickenLog, Display, TEXT("Attacking"));
	bIsDamageDone = false;
}

//void AKP_AIChicken::BeginPlay()
//{
//	Super::BeginPlay();
//
//	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
//	QuestSubsystem->AddQuestActor(this, KillableActorClass);
//
//	
//	//UE_LOG(AIChickenLog, Display, TEXT("%s"), *GetWorld()->GetCurrentLevel()->GetName());
//}
