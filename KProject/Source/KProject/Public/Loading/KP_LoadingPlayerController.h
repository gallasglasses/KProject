#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KP_LoadingPlayerController.generated.h"

UCLASS()
class KPROJECT_API AKP_LoadingPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
