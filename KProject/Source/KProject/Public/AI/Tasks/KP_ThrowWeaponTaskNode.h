//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "BehaviorTree/BTTaskNode.h"
//#include "KP_ThrowWeaponTaskNode.generated.h"
//
//class AKP_AICharacter;
//
//UCLASS()
//class KPROJECT_API UKP_ThrowWeaponTaskNode : public UBTTaskNode
//{
//	GENERATED_BODY()
//
//public:
//	UKP_ThrowWeaponTaskNode();
//
//	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
//
//protected:
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
//		FBlackboardKeySelector EnemyActorKey;
//		
//private:
//
//	FTimerHandle AttackTimerHandle;
//	float TimerDelay = 1.6;
//	void SentSignalToAttack();
//	AKP_AICharacter* Damager;
//
//};
