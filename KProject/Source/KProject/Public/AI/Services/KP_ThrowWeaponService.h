// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KP_ThrowWeaponService.generated.h"

UCLASS()
class KPROJECT_API UKP_ThrowWeaponService : public UBTService
{
	GENERATED_BODY()

public:

	UKP_ThrowWeaponService();

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
