// Fill out your copyright notice in the Description page of Project Settings.

#include "LocationMarkerActor.h"

void ALocationMarkerActor::OnOverlapByActor(AActor* OverlappingActor)
{
	NotifyOverlapWithActor(this, OverlappingActor);
}