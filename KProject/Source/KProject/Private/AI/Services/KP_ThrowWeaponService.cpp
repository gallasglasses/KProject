// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KP_ThrowWeaponService.h"
#include "AI/KP_AICharacter.h"
#include "Components/KP_WeaponComponent.h"
#include "KP_Utils.h"

#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"

UKP_ThrowWeaponService::UKP_ThrowWeaponService()
{
	NodeName = "ThrowWeapon";
}

void UKP_ThrowWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);


	if (Controller)
	{
		const auto WeaponComponent = KP_Utils::GetPlayerComponent<UKP_WeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->OnWantToStart() : WeaponComponent->OnWantToStop();
		}
		
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
