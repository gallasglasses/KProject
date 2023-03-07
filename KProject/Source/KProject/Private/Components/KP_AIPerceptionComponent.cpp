// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KP_AIPerceptionComponent.h"
#include "Components/KP_HealthComponent.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "AI/KP_AIController.h"
#include "Player/KP_BaseCharacter.h"
#include "KP_Utils.h"

#include "AIController.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(AIPerceptionLog, All, All);

AActor* UKP_AIPerceptionComponent::GetClosetEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AKP_AIController>(GetOwner()); //<AAIController>
	if(!Controller) return nullptr;

	const auto Pawn = Controller-> GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for ( const auto PercieveActor : PercieveActors)
	{
		if (!PercieveActor) return nullptr;

		const auto BehaviorType = Controller->GetTeamAttitudeTowards(*PercieveActor);

		const auto HealthComponent = KP_Utils::GetPlayerComponent<UKP_HealthComponent>(PercieveActor);
		if (BehaviorType == ETeamAttitude::Hostile && HealthComponent && !HealthComponent->IsDead()) //TODO: check if enemies or not
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
