// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "KP_CoreTypes.h"
#include "KP_AIController.generated.h"

class UKP_AIPerceptionComponent;

UCLASS()
class KPROJECT_API AKP_AIController : public AAIController
{
	GENERATED_BODY()

public: 

	AKP_AIController();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION(BlueprintCallable, Category = "Behavior Type")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	UFUNCTION(BlueprintCallable, Category = "Behavior Type")
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_AIPerceptionComponent* KP_AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior Type")
	EBehaviorType InitialTeam;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
private:
		
	AActor* GetFocusOnActor() const;
};
