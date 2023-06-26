#include "KP_GameInstance.h"
#include "UObject/SoftObjectPtr.h"

TSoftObjectPtr<UWorld> UKP_GameInstance::GetLevel(EGameLevel NewLevel) const
{
	if (!Levels.Find(NewLevel)) return nullptr;
	
	return Levels[NewLevel];
}
