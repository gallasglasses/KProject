// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/KP_AIFactory.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AIFactoryLog, All, All);

AKP_AIFactory::AKP_AIFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("Spawn Point");
	SpawnPoint->SetupAttachment(GetRootComponent());
}

void AKP_AIFactory::BeginPlay()
{
	Super::BeginPlay();

	StartSpawnActorsTimer();
}

void AKP_AIFactory::StartSpawnActorsTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AKP_AIFactory::SpawnActors, SpawnRate, true, SpawnRate);
}

void AKP_AIFactory::SpawnActors()
{
	if (!GetWorld()) return;

	UE_LOG(AIFactoryLog, Display, TEXT("SpawnedActorsCount: %i"), SpawnedActorsCount);
	FTransform SpawnTransform(SpawnPoint->GetComponentRotation(), SpawnPoint->GetComponentLocation(), FVector(1.f));
	const auto KP_AIActor = GetWorld()->SpawnActorDeferred<APawn>(AIPawnClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	KP_AIActor->FinishSpawning(SpawnTransform);	
	
	if (SpawnedActorsCount + 1 < GameData.AIPlayersNum)
	{
		++SpawnedActorsCount;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		UE_LOG(AIFactoryLog, Display, TEXT("ClearTimer"));
	}


	//for (int32 i = 0; i < GameData.AIPlayersNum; ++i)
	//{
	//	// UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), AIPawnClass, ,SpawnPoint->GetComponentLocation())

	//	// FActorSpawnParameters SpawnInfo;
	//	// SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	// const auto KP_AIActor = GetWorld()->SpawnActor<APawn>(AIPawnClass, SpawnInfo);
	//}
}

