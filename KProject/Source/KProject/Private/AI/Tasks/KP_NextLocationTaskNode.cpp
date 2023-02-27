// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/KP_NextLocationTaskNode.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"



UKP_NextLocationTaskNode::UKP_NextLocationTaskNode()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UKP_NextLocationTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSys) return EBTNodeResult::Failed;
	
	FNavLocation NavLocation;
	auto PawnLocation = Pawn->GetActorLocation();

	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor) return EBTNodeResult::Failed;
		if(CenterActor->GetVelocity().Size() == 0.f) return EBTNodeResult::Failed;
		PawnLocation = CenterActor->GetActorLocation();
	}

	const auto Found = NavSys->GetRandomReachablePointInRadius(PawnLocation, Radius, NavLocation);
	if (!Found) return EBTNodeResult::Failed;
	
	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}
