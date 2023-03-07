// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KP_IsPlayerInRangeService.generated.h"

UCLASS()
class KPROJECT_API UKP_IsPlayerInRangeService : public UBTService
{
	GENERATED_BODY()

public:

	UKP_IsPlayerInRangeService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector IsPlayerInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AttackRange = 150.f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
