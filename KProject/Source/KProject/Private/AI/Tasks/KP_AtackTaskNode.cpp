// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/KP_AtackTaskNode.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "Components/KP_WeaponComponent.h"
#include "KP_Utils.h"

#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(AtackTaskNodeLog, All, All);

UKP_AtackTaskNode::UKP_AtackTaskNode()
{
	NodeName = "Attack Enemy";
}

EBTNodeResult::Type UKP_AtackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	const auto IsInRange = Blackboard && Blackboard->GetValueAsBool(IsPlayerInRange.SelectedKeyName);

	if (!Controller) return EBTNodeResult::Failed;

	const auto OwnerController = Cast<AKP_AIBaseEnemyCharacter>(Controller->GetPawn());
	if (OwnerController->HasSpawnWeapon)
	{
		const auto WeaponComponent = KP_Utils::GetPlayerComponent<UKP_WeaponComponent>(Controller->GetPawn());
		if (!WeaponComponent) return EBTNodeResult::Failed;
		HasAim && IsInRange ? WeaponComponent->OnWantToStart() : WeaponComponent->OnWantToStop();
	}
	else
	{
		//UE_LOG(AtackTaskNodeLog, Display, TEXT("HasAim %s"), HasAim ? TEXT("true") : TEXT("false"));
		//UE_LOG(AtackTaskNodeLog, Display, TEXT("IsInRange %s"), IsInRange ? TEXT("true") : TEXT("false"));
		HasAim && IsInRange ? OwnerController->OnStartAttacking() : OwnerController->OnStopAttacking();
	}

	return EBTNodeResult::Succeeded;
}
