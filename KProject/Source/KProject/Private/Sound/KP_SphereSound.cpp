// Fill out your copyright notice in the Description page of Project Settings.

#include "Sound/KP_SphereSound.h"
#include "Player/KP_BaseCharacter.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(SphereSoundLog, All, All);

AKP_SphereSound::AKP_SphereSound()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(CollisionComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(CollisionComponent); 
}

void AKP_SphereSound::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->SetSphereRadius(SphereRadius, true);
	if (SoundCue && SoundAttenuation)
	{
		AudioComponent->SetSound(SoundCue);
		AudioComponent->AttenuationSettings = SoundAttenuation;
	}
}

void AKP_SphereSound::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto KP_BaseCharacter = Cast<AKP_BaseCharacter>(OtherActor);
	if (KP_BaseCharacter)
	{
		if (bIsRandomPlay)
		{
			AudioComponent->Play(FMath::RandRange(0.f, SoundCue->Duration));
			UE_LOG(SphereSoundLog, Display, TEXT("Sound Random play"));
		}
		else
		{
			AudioComponent->Play(); 
			UE_LOG(SphereSoundLog, Display, TEXT("Sound play"));
		}
	}
}

