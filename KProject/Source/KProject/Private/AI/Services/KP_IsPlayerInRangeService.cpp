// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KP_IsPlayerInRangeService.h"
#include "AI/KP_AIController.h"
#include "Components/KP_AIPerceptionComponent.h"
#include "KP_Utils.h"

#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(IsPlayerInRangeServiceLog, All, All);

UKP_IsPlayerInRangeService::UKP_IsPlayerInRangeService()
{
	NodeName = "IsPlayerInRange";
}

void UKP_IsPlayerInRangeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = Cast<AKP_AIController>(OwnerComp.GetAIOwner());//
		const auto PerceptionComponent = KP_Utils::GetPlayerComponent<UKP_AIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			if (PerceptionComponent->GetClosetEnemy())
			{
				const auto Distance = FVector::Distance(Controller->GetPawn()->GetActorLocation(), PerceptionComponent->GetClosetEnemy()->GetActorLocation());
				//UE_LOG(IsPlayerInRangeServiceLog, Display, TEXT("Distance: %f"), Distance);
				const auto bIsPlayerInRange = Distance <= AttackRange;
				UE_LOG(IsPlayerInRangeServiceLog, Display, TEXT("bIsPlayerInRange %s"), bIsPlayerInRange ? TEXT("true") : TEXT("false"));

				Blackboard->SetValueAsBool(IsPlayerInRange.SelectedKeyName, bIsPlayerInRange);
			}
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
