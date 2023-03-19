#pragma once

#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "KP_CoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 AIPlayersNum = 10;
};

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Neutral = 0,
	Friend = 1,
	Monster = 2
};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	InPlayerMenu,
	Death,
	GameOver
};

UENUM(BlueprintType)
enum class EGameLocation : uint8
{
	Nowhere = 0,
	Kalevala,
	Pohjola,
	Manala,
	Metsola,
	Louhi,
	Saari,
	Sea
};

//UENUM(BlueprintType)
//enum class EGameLocalization : uint8
//{
//	en UMETA(DisplayName = "English"),
//	ru UMETA(DisplayName = "Русский"),
//	sv UMETA(DisplayName = "Svenska"),
//	fi UMETA(DisplayName = "Suomi")
//};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameLocationChangedSignature, EGameLocation);

USTRUCT(BlueprintType)
struct FMusicLocationInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location")
		EGameLocation GameLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		USoundCue* SoundCue;
};

USTRUCT(BlueprintType)
struct FGameLocalizationInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Option;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Culture;
};