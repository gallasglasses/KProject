//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "AI/Tasks/KP_ThrowWeaponTaskNode.h"
//#include "AI/KP_AICharacter.h"
//
//#include "BehaviorTree/BlackBoardComponent.h"
//#include "AIController.h"
//
//UKP_ThrowWeaponTaskNode::UKP_ThrowWeaponTaskNode()
//{
//	NodeName = "Throw Weapon";
//}
//
//EBTNodeResult::Type UKP_ThrowWeaponTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	const auto Blackboard = OwnerComp.GetBlackboardComponent();
//	const auto Controller = OwnerComp.GetAIOwner();
//
//	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
//
//
//	if (Controller)
//	{
//		const auto Instigator = Cast<AKP_AICharacter>(Controller->GetOwner());
//
//		if (Instigator)
//		{
//
//			if (HasAim)
//			{
//				Damager = Instigator;
//				Damager->OnStartAttacking();
//				//GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UKP_ThrowWeaponTaskNode::SentSignalToAttack, TimerDelay, false);
//			}
//			else
//			{
//				Instigator->OnStopAttacking();
//
//				//GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
//			}
//		}
//		else return EBTNodeResult::Failed;
//	}
//	else return EBTNodeResult::Failed;
//
//	return EBTNodeResult::Succeeded;
//}
//
//void UKP_ThrowWeaponTaskNode::SentSignalToAttack()
//{
//	Damager->OnStartAttacking();
//
//	//GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
//}