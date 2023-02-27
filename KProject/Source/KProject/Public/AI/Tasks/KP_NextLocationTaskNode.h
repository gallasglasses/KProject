// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KP_NextLocationTaskNode.generated.h"

UCLASS()
class KPROJECT_API UKP_NextLocationTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UKP_NextLocationTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
