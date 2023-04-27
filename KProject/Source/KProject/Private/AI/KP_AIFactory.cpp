// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/KP_AIFactory.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "QuestSubsystem.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(AIFactoryLog, All, All);

AKP_AIFactory::AKP_AIFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	FactoryBox = CreateDefaultSubobject<UBoxComponent>("Spawn Box");
	FactoryBox->SetupAttachment(GetRootComponent());

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("Spawn Point");
	SpawnPoint->SetupAttachment(FactoryBox);
}

void AKP_AIFactory::BeginPlay()
{
	Super::BeginPlay();

	//StartSpawnActorsTimer();

	for (; SpawnedActorsCount < AIPlayersNum; ++SpawnedActorsCount)
	{
		SpawnActors();
	}
}

void AKP_AIFactory::StartSpawnActorsTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AKP_AIFactory::SpawnActors, SpawnRate, true, SpawnRate);
}

void AKP_AIFactory::SpawnActors()
{
	if (!GetWorld()) return;

	UE_LOG(AIFactoryLog, Display, TEXT("SpawnedActorsCount: %i"), SpawnedActorsCount);

	/*FTransform SpawnTransform(SpawnPoint->GetComponentRotation(), SpawnPoint->GetComponentLocation(), FVector(1.f));
	const auto KP_AIActor = GetWorld()->SpawnActorDeferred<APawn>(AIPawnClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	KP_AIActor->FinishSpawning(SpawnTransform);	*/

	
	FVector BoundsCenter = FactoryBox->GetRelativeLocation();
	UE_LOG(AIFactoryLog, Display, TEXT("Bounds Center: %s"), *BoundsCenter.ToString());
	FVector BoundsExtent = FactoryBox->GetScaledBoxExtent();
	UE_LOG(AIFactoryLog, Display, TEXT("Bounds Extent: %s"), *BoundsExtent.ToString());
	const auto BoundsRotator = FactoryBox->GetRelativeRotation();
	UE_LOG(AIFactoryLog, Display, TEXT("Bounds Rotator: %s"), *BoundsRotator.ToString());

	FVector BoundsExtentAtAngle = BoundsRotator.RotateVector(BoundsExtent);
	UE_LOG(AIFactoryLog, Display, TEXT("Bounds Extent At Angle: %s"), *BoundsExtentAtAngle.ToString());

	const auto BoundFactoryBox = FBox(BoundsCenter - BoundsExtentAtAngle * 0.5f, BoundsCenter + BoundsExtentAtAngle * 0.5f);

	FVector RandomPointInFactoryBox = FMath::RandPointInBox(BoundFactoryBox);
	//RandomPointInFactoryBox.Z = BoundsCenter.Z - BoundsExtent.Z * 0.5f;
	UE_LOG(AIFactoryLog, Display, TEXT("Random Point In Factory Box: %s"), *RandomPointInFactoryBox.ToString());
	FRotator RandSpawnYawRotator = FRotator::ZeroRotator;
	RandSpawnYawRotator.Yaw = FMath::RandRange(0.f, 360.f);
	UE_LOG(AIFactoryLog, Display, TEXT("Rand Spawn Yaw Rotator: %f"), RandSpawnYawRotator.Yaw);
	FTransform SpawnTransform(RandSpawnYawRotator, RandomPointInFactoryBox, FVector(1.f));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = this;
	SpawnParameters.OverrideLevel = this->GetLevel();

	//UE_LOG(AIFactoryLog, Display, TEXT("%s"), *this->GetLevel()->GetName());

	const auto KP_AIActor = GetWorld()->SpawnActor<APawn>(AIPawnClass, SpawnParameters);
	KP_AIActor->SetActorTransform(SpawnTransform);


	// with spawn timer
	//if (SpawnedActorsCount + 1 < AIPlayersNum ) //GameData.AIPlayersNum
	//{
	//	++SpawnedActorsCount;
	//}
	//else
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	//	UE_LOG(AIFactoryLog, Display, TEXT("ClearTimer"));
	//}
}

