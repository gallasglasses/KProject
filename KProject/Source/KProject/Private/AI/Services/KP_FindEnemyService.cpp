// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KP_FindEnemyService.h"
#include "AI/KP_AIController.h"
#include "Components/KP_AIPerceptionComponent.h"
#include "KP_Utils.h"

#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

UKP_FindEnemyService::UKP_FindEnemyService()
{
	NodeName = "FindEnemy";
}

void UKP_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = Cast<AKP_AIController>(OwnerComp.GetAIOwner());//
		const auto PerceptionComponent = KP_Utils::GetPlayerComponent<UKP_AIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosetEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
