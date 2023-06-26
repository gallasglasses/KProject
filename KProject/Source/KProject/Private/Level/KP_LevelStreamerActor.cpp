#include "Level/KP_LevelStreamerActor.h"
#include "KP_GameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogLevelStreamerActor, All, All);

AKP_LevelStreamerActor::AKP_LevelStreamerActor()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	SetRootComponent(OverlapVolume);

	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &AKP_LevelStreamerActor::OnBeginOverlap);
	OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &AKP_LevelStreamerActor::OnEndOverlap);
}

void AKP_LevelStreamerActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;
	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	const auto MyCharacter = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == MyCharacter && !KP_GameInstance->GetLevel(LevelToLoad).IsNull())
	{
		UE_LOG(LogLevelStreamerActor, Display, TEXT("LoadStreamLevelBySoftObjectPtr"));
		FLatentActionInfo LatentInfo;
		LatentInfo.UUID = 1;
		LatentInfo.Linkage = LatentInfo.UUID;
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, KP_GameInstance->GetLevel(LevelToLoad), true, false, LatentInfo);
	}
}

void AKP_LevelStreamerActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!GetWorld()) return;
	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	const auto MyCharacter = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == MyCharacter && !KP_GameInstance->GetLevel(LevelToUnload).IsNull())
	{
		UE_LOG(LogLevelStreamerActor, Display, TEXT("UnloadStreamLevelBySoftObjectPtr"));
		FLatentActionInfo LatentInfo;
		LatentInfo.UUID = 1;
		LatentInfo.Linkage = LatentInfo.UUID;
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, KP_GameInstance->GetLevel(LevelToUnload), LatentInfo, false);
	}
	
}

