// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/KP_SoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(SoundFuncLibLog, All, All);

void UKP_SoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f);
	UE_LOG(SoundFuncLibLog, Display, TEXT("%s : %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
}

void UKP_SoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;
	
	const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
	SetSoundClassVolume(SoundClass, NextVolume);
}
