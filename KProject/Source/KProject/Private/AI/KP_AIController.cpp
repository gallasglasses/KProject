// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KP_AIController.h"
#include "AI/KP_AICharacter.h"
#include "Components/KP_AIPerceptionComponent.h"

#include "BehaviorTree/BlackBoardComponent.h"

AKP_AIController::AKP_AIController()
{
	KP_AIPerceptionComponent = CreateDefaultSubobject<UKP_AIPerceptionComponent>("KP_AIPerceptionComponent");
	SetPerceptionComponent(*KP_AIPerceptionComponent);
}

void AKP_AIController::BroadcastEnemyLocation(FVector ActorLocation)
{
	OnFindEnemy.Broadcast(ActorLocation);
}

void AKP_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto KP_AICharacter = Cast<AKP_AICharacter>(InPawn);
	if (KP_AICharacter)
	{
		RunBehaviorTree(KP_AICharacter->BehaviorTreeAsset);
	}
}

void AKP_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//const auto AimActor = KP_AIPerceptionComponent->GetClosetEnemy();
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AKP_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
