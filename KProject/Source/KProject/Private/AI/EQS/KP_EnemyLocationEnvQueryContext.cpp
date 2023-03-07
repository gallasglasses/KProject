// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/KP_EnemyLocationEnvQueryContext.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UKP_EnemyLocationEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get()); 
	const auto BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!BlackBoard) return;

	const auto ContextActor = BlackBoard->GetValueAsObject(EnemyActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
