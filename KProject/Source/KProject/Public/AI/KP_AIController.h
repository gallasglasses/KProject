// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KP_AIController.generated.h"

class UKP_AIPerceptionComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFindEnemySignature, FVector);

UCLASS()
class KPROJECT_API AKP_AIController : public AAIController
{
	GENERATED_BODY()

public: 

	AKP_AIController();

	void BroadcastEnemyLocation(FVector ActorLocation);//

	FOnFindEnemySignature OnFindEnemy;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKP_AIPerceptionComponent* KP_AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";	

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
private:
		
	AActor* GetFocusOnActor() const;
};
