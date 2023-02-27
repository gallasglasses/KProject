// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/KP_ChaseEnemyTaskNode.h"
#include "AI/KP_AIController.h"
#include "blackboard_keys.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UKP_ChaseEnemyTaskNode::UKP_ChaseEnemyTaskNode()
{
	NodeName = "Chase Enemy";
}

EBTNodeResult::Type UKP_ChaseEnemyTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<AKP_AIController>(OwnerComp.GetAIOwner());
	const auto EnemyLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(bb_keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, EnemyLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
