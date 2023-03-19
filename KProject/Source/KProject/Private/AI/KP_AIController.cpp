// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KP_AIController.h"
#include "AI/KP_AIBaseEnemyCharacter.h"
#include "Components/KP_AIPerceptionComponent.h"

#include "BehaviorTree/BlackBoardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AKP_AIControllerLog, All, All);

AKP_AIController::AKP_AIController()
{
	KP_AIPerceptionComponent = CreateDefaultSubobject<UKP_AIPerceptionComponent>("KP_AIPerceptionComponent");
	SetPerceptionComponent(*KP_AIPerceptionComponent);

	//bWantsPlayerState = true;
}

ETeamAttitude::Type AKP_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamAttitude::Type Attitude;
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		Attitude = FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId());
	}
	else
	{
		/*if (&Other)
		{
			UE_LOG(AKP_AIControllerLog, Error, TEXT("%s is no TeamAgent"), *Other.GetName());
		}*/
		Attitude = ETeamAttitude::Neutral;
	}

	//UE_LOG(AKP_AIControllerLog, Display, TEXT("Neutral %s"), Attitude == ETeamAttitude::Neutral ? TEXT("true") : TEXT("false"));
	//UE_LOG(AKP_AIControllerLog, Display, TEXT("Friendly %s"), Attitude == ETeamAttitude::Friendly ? TEXT("true") : TEXT("false"));
	//UE_LOG(AKP_AIControllerLog, Display, TEXT("Hostile %s"), Attitude == ETeamAttitude::Hostile ? TEXT("true") : TEXT("false"));
	return Attitude;

	/*const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (TeamAgent)
	{
		FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
		if (OtherTeamID == 0) 
		{
			return ETeamAttitude::Hostile;
		}
		else if (OtherTeamID == 1)
		{
			return ETeamAttitude::Friendly;
		}
		else 
		{
			return ETeamAttitude::Neutral;
		}
	}
	return ETeamAttitude::Neutral;*/
}

void AKP_AIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	IGenericTeamAgentInterface* ControlledAgent = Cast<IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		ControlledAgent->SetGenericTeamId(NewTeamID);
	}
}

FGenericTeamId AKP_AIController::GetGenericTeamId() const
{
	const IGenericTeamAgentInterface* ControlledAgent = Cast<const IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		return ControlledAgent->GetGenericTeamId();
	}

	return FGenericTeamId();
}

void AKP_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto KP_AIBaseCharacter = Cast<AKP_AIBaseEnemyCharacter>(InPawn);
	if (KP_AIBaseCharacter)
	{
		RunBehaviorTree(KP_AIBaseCharacter->BehaviorTreeAsset);
	}
}

void AKP_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//const auto AimActor = KP_AIPerceptionComponent->GetClosetEnemy();
	const auto AimActor = GetFocusOnActor();
	if (!AimActor) return;
	SetFocus(AimActor);
}

AActor* AKP_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
