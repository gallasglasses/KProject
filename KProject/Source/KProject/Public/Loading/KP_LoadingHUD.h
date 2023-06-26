#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KP_LoadingHUD.generated.h"

UCLASS()
class KPROJECT_API AKP_LoadingHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> LoadingWidgetClass;

	virtual void BeginPlay() override;
	
};
