#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KP_CoreTypes.h"
#include "KP_LevelStreamerActor.generated.h"

class UBoxComponent;

UCLASS()
class KPROJECT_API AKP_LevelStreamerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKP_LevelStreamerActor();

protected:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	EGameLevel LevelToLoad;

	UPROPERTY(EditAnywhere)
	EGameLevel LevelToUnload;

private:

	// Overlap volume to trigger level streaming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* OverlapVolume;

};
