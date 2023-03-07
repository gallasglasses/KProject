// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/People/KP_AIEnemyWitch.h"
#include "Components/KP_WeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AIWitchLog, All, All);

AKP_AIEnemyWitch::AKP_AIEnemyWitch(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	
}

bool AKP_AIEnemyWitch::IsThrowingWeapon() const
{
	return bIsThrowingWeapon;
}

void AKP_AIEnemyWitch::SetThrowing(bool bIsActing)
{
	bIsThrowingWeapon = bIsActing;

	if (bIsThrowingWeapon)
	{
		UE_LOG(AIWitchLog, Display, TEXT("Throwing Weapon"));
		WeaponComponent->WeaponAttack();
	}
}
