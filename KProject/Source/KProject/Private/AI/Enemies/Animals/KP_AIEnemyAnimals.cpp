// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/Animals/KP_AIEnemyAnimals.h"
#include "Components/KP_HealthComponent.h"
#include "AI/KP_AIController.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AIEnemyAnimalsLog, All, All);

AKP_AIEnemyAnimals::AKP_AIEnemyAnimals(const FObjectInitializer& ObjInit) :Super(ObjInit)
{
	TriggerHitComponent = CreateDefaultSubobject<UBoxComponent>("TriggerHitComponent");
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	TriggerHitComponent->AttachToComponent(GetMesh(), AttachmentRules, "TriggerHitSocket");
	TriggerHitComponent->OnComponentBeginOverlap.AddDynamic(this, &AKP_AIEnemyAnimals::OnOverlapHit);
	TriggerHitComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

void AKP_AIEnemyAnimals::MakeDamage(const FHitResult& HitResult)
{
	const auto HitActor = HitResult.GetActor();

	UE_LOG(AIEnemyAnimalsLog, Display, TEXT("bIsDamageDone %s"), bIsDamageDone ? TEXT("true") : TEXT("false"));
	const auto Distance = FVector::Distance(HitActor->GetActorLocation(), GetActorLocation());
	UE_LOG(AIEnemyAnimalsLog, Display, TEXT("Distance %f"), Distance);

	bIsInRange = (Distance <= AttackRange);

	UE_LOG(AIEnemyAnimalsLog, Display, TEXT("bIsInRange %s"), bIsInRange ? TEXT("true") : TEXT("false"));
	if (!bIsDamageDone && bIsInRange)
	{
		UE_LOG(AIEnemyAnimalsLog, Display, TEXT("Damage done"));
		HitActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
		bIsDamageDone = true;
	}
}

APlayerController* AKP_AIEnemyAnimals::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		return nullptr;
	}
	return Player->GetController<APlayerController>();
}

void AKP_AIEnemyAnimals::OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking())
	{
		const auto HitActor = SweepResult.GetActor();
		if (!HitActor)
		{
			return;
		}
		if (HitActor == this)
		{
			return;
		}

		const auto KP_AIController = Cast<AKP_AIController>(GetController());
		if (KP_AIController && KP_AIController->GetTeamAttitudeTowards(*OtherActor) == ETeamAttitude::Hostile)
		{
			UE_LOG(AIEnemyAnimalsLog, Display, TEXT("Hostile: %s, you got damage"), *SweepResult.GetActor()->GetName());
			MakeDamage(SweepResult);
		}
		else
		{
			UE_LOG(AIEnemyAnimalsLog, Display, TEXT("Friendly"));
		}
	}
}
