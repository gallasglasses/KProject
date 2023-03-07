#pragma once

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
