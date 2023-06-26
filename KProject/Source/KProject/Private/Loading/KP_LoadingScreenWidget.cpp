#include "Loading/KP_LoadingScreenWidget.h"
#include "KP_GameInstance.h"
#include "KP_CoreTypes.h"
#include "KProjectGameModeBase.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LevelStreaming.h"
#include "UObject/UObjectGlobals.h"

DEFINE_LOG_CATEGORY_STATIC(WBPLoadingScreenLog, All, All);

void UKP_LoadingScreenWidget::FadeInAnimation()
{
	PlayAnimation(FadeInAnim);
	LoadLevel();
}

void UKP_LoadingScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UKP_LoadingScreenWidget::OnStartGame);
	}
}

void UKP_LoadingScreenWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != FadeOutAnim) return;

	if (GetWorld())
	{
		const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->StartGame();
		}
	}
}

void UKP_LoadingScreenWidget::OnStartGame()
{
	PlayAnimation(FadeOutAnim);
}

void UKP_LoadingScreenWidget::LoadLevel()
{

	if (!GetWorld()) return;
	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return;

	if (KP_GameInstance->GetLevel(EGameLevel::LevelBB).IsNull())
	{
		UE_LOG(WBPLoadingScreenLog, Error, TEXT("Level name is NONE"));
		return;
	}

	/*LoadPackageAsync(KP_GameInstance->GetSubLevelName_BB().ToString(),
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
				{
					LevelFinishedLoad();
				}
			}),
		0,
		PKG_ContainsMap);*/

	FLatentActionInfo LatentInfo; 
	//LatentInfo.CallbackTarget = this;
	//LatentInfo.ExecutionFunction = "LevelFinishedLoad";
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = LatentInfo.UUID;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), KP_GameInstance->GetLevel(EGameLevel::LevelBB), true, false, LatentInfo);
	FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UKP_LoadingScreenWidget::LevelFinishedLoad);
}

void UKP_LoadingScreenWidget::LevelFinishedLoad(ULevel* Level, UWorld* World)
{
	LoadingSwitcher->SetActiveWidgetIndex(1); 
	if (GetWorld())
	{
		const auto GameMode = Cast<AKProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->TurnOffGlobalGravitySet(); //this is a temporary solution
		}
	}
}

FName UKP_LoadingScreenWidget::GetLevelNameFromGameInstance()
{
	if (!GetWorld()) return FName(NAME_None);
	const auto KP_GameInstance = GetWorld()->GetGameInstance<UKP_GameInstance>();
	if (!KP_GameInstance) return FName(NAME_None);

	if (KP_GameInstance->GetMainLevelName().IsNone())
	{
		UE_LOG(WBPLoadingScreenLog, Error, TEXT("Level name is NONE"));
		return FName(NAME_None);
	}
	return KP_GameInstance->GetMainLevelName();
}
