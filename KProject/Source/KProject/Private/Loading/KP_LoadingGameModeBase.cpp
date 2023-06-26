#include "Loading/KP_LoadingGameModeBase.h"
#include "Loading/KP_LoadingHUD.h"

AKP_LoadingGameModeBase::AKP_LoadingGameModeBase()
{
	HUDClass = AKP_LoadingHUD::StaticClass();
}
