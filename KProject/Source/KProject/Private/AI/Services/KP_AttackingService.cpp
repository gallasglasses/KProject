// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KP_AttackingService.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "Components/KP_WeaponComponent.h"
#include "KP_Utils.h"

#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(AIServiceLog, All, All);

UKP_AttackingService::UKP_AttackingService()
{
	NodeName = "Attacking";
}

void UKP_AttackingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);


	if (Controller)
	{
		const auto OwnerController = Cast<AKP_AIBaseEnemyCharacter>(Controller->GetPawn());
		if (OwnerController->HasSpawnWeapon)
		{
			const auto WeaponComponent = KP_Utils::GetPlayerComponent<UKP_WeaponComponent>(Controller->GetPawn());
			if (WeaponComponent)
			{
				HasAim ? WeaponComponent->OnWantToStart() : WeaponComponent->OnWantToStop();
			}
		}
		else
		{
			//UE_LOG(AIServiceLog, Display, TEXT("HasAim %s"), HasAim ? TEXT("true") : TEXT("false"));
			HasAim ? OwnerController->OnStartAttacking() : OwnerController->OnStopAttacking();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
