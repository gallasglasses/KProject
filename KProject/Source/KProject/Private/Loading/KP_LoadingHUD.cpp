#include "Loading/KP_LoadingHUD.h"
//#include "Blueprint/UserWidget.h"
#include "Loading/KP_LoadingScreenWidget.h"

void AKP_LoadingHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LoadingWidgetClass)
	{
		const auto LoadingWidget = CreateWidget<UKP_LoadingScreenWidget>(GetWorld(), LoadingWidgetClass);
		if (LoadingWidget)
		{
			LoadingWidget->AddToViewport();
			LoadingWidget->FadeInAnimation();
		}
	}
}
