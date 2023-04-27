// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/KP_AIBaseEnemyCharacter.h"
#include "AI/KP_AIController.h"
#include "Player/KP_BaseCharacter.h"

#include "QuestSubsystem.h"

#include "Components/KP_AIMovementComponent.h"
#include "Components/KP_HealthComponent.h"
#include "Components/KP_StaminaComponent.h"
#include "Components/KP_ManaComponent.h"
#include "Components/KP_WeaponComponent.h"

#include "UI/KP_HealthBarWidget.h"

#include "Weapons/KP_Dagger.h"

//ue h
#include "BrainComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(AIBaseEnemyCharacterLog, All, All);

AKP_AIBaseEnemyCharacter::AKP_AIBaseEnemyCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UKP_AIMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessAI = EAutoPossessAI::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AKP_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	}

	HealthComponent = CreateDefaultSubobject<UKP_HealthComponent>("HealthComponent");

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->bOwnerNoSee = false;
	//HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HealthWidgetComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	HealthWidgetComponent->SetDrawAtDesiredSize(true);

	WeaponComponent = CreateDefaultSubobject<UKP_WeaponComponent>("WeaponComponent");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	//OnDestroyed.AddDynamic(this, &ThisClass::OnDestroyAKillableActor);
}

bool AKP_AIBaseEnemyCharacter::IsRunning() const
{
	return bWantsToRun && !GetVelocity().IsZero();;
}

void AKP_AIBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthWidgetComponent);
	check(GetCharacterMovement());
	check(WeaponComponent);

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeathByInstigator.AddUObject(this, &AKP_AIBaseEnemyCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AKP_AIBaseEnemyCharacter::OnHealthChanged);

	WeaponComponent->OnWantToStartAttack.AddUObject(this, &AKP_AIBaseEnemyCharacter::OnStartAttacking);
	WeaponComponent->OnWantToStopAttack.AddUObject(this, &AKP_AIBaseEnemyCharacter::OnStopAttacking);

	LandedDelegate.AddDynamic(this, &AKP_AIBaseEnemyCharacter::OnGroundLanded);

	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->AddQuestActor(this, KillableActorClass);
}

void AKP_AIBaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AKP_AIBaseEnemyCharacter::IsAttacking() const
{
	return bIsAttacking;
}

bool AKP_AIBaseEnemyCharacter::CanAttack() const
{
	return !HealthComponent->IsDead();
}

void AKP_AIBaseEnemyCharacter::Kill_Implementation(AActor* InteractInstigator)
{
	UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("InteractInstigator: %s"), *InteractInstigator->GetName());
	if (InteractInstigator == nullptr)
	{
		return;
	}
	UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Kill_Implementation"));
	
	if (HealthComponent->IsDead() && InteractInstigator)
	{
		NotifyKillingFinished(this, InteractInstigator);
		if (HasAnimMontage)
		{
			//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("DeathAnimMontage"));
			PlayAnimMontage(DeathAnimMontage);
			SetLifeSpan(DeathAnimMontage->CalculateSequenceLength() - 0.5f);
		}
		else
		{
			SetLifeSpan(1.f);
		}
	}
}

float AKP_AIBaseEnemyCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AKP_AIBaseEnemyCharacter::OnKillingFinished(AActor* ActorKilledObject)
{
	NotifyKillingFinished(this, ActorKilledObject);
}

void AKP_AIBaseEnemyCharacter::OnDestroyKillableActor(AActor* Actor)
{
	auto QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
	QuestSubsystem->RemoveQuestActor(Actor);
}

void AKP_AIBaseEnemyCharacter::OnStartAttacking()
{
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("On Melee Attack"));
	MeleeAttack();
}

void AKP_AIBaseEnemyCharacter::OnStopAttacking()
{
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("On Stop Attack"));
	StopAttack();
}

void AKP_AIBaseEnemyCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("On Ground Landed %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Final Damage %f"), FinalDamage);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AKP_AIBaseEnemyCharacter::Block()
{

}

void AKP_AIBaseEnemyCharacter::OnDeath(AActor* Killer)
{
	UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("%s, You are dead"), *GetName());
	const auto AIController = Cast<AKP_AIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("BrainComponent->Cleanup"));
		AIController->BrainComponent->Cleanup();
	}
	
	GetCharacterMovement()->DisableMovement(); //UCharacterMovementComponent * GetCharacterMovement() const
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->OnWantToStop();
	
	if (!Cast<AKP_BaseCharacter>(Killer))
	{
		AIDestroy();
	}
}

void AKP_AIBaseEnemyCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	const auto HealthBarWidget = Cast<UKP_HealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		return;
	}
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
	HealthBarWidget->SetScaleDamage(HealthDelta);
}

void AKP_AIBaseEnemyCharacter::MeleeAttack()
{
	if (bIsAttacking)
	{
		bIsComboAttack = true;
		//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Attacking yet and save"));
	}
	else
	{
		bIsAttacking = true;
		//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Attacking now"));
		if (HasAnimMontage)
		{
			ChooseComboAnimMontage();
		}
		else
		{
			Attacking();
		}
	}
}

void AKP_AIBaseEnemyCharacter::Attacking()
{
	//...

	ResetCombo();
}

void AKP_AIBaseEnemyCharacter::ChooseComboAnimMontage()
{
	if (AttackAnimMontages.IsValidIndex(ComboAttackCount))
	{
		OnPlayAnimMontage(ComboAttackCount);
		if (ComboAttackCount >= 0)
		{
			ComboAttackCount++;
		}
		if (ComboAttackCount == AttackAnimMontages.Num())
		{
			ComboAttackCount = 0;
		}
	}
}

void AKP_AIBaseEnemyCharacter::OnPlayAnimMontage(int8 Count)
{
	if (bIsAttacking)
	{
		PlayAnimMontage(AttackAnimMontages[Count]);
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKP_AIBaseEnemyCharacter::ComboAttackSave, AttackAnimMontages[Count]->CalculateSequenceLength(), false);
		//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Play Attack %d"), Count);
	}
}

void AKP_AIBaseEnemyCharacter::ComboAttackSave()
{
	if (bIsComboAttack)
	{
		bIsDamageDone = false;
		bIsComboAttack = false;
		ChooseComboAnimMontage();
	}
	else
	{
		ResetCombo();
	}
}

void AKP_AIBaseEnemyCharacter::ResetCombo()
{
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Reset Combo"));
	ComboAttackCount = 0;
	bIsComboAttack = false;
	StopAttack();
}

void AKP_AIBaseEnemyCharacter::StopAttack()
{
	bIsAttacking = false;
	bIsDamageDone = false;
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("bIsDamageDone %s"), bIsDamageDone ? TEXT("true") : TEXT("false"));
	//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("Stop Attack"));
	if (HasAnimMontage)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	}
}

void AKP_AIBaseEnemyCharacter::AIDestroy()
{
	if (HasAnimMontage)
	{
		//UE_LOG(AIBaseEnemyCharacterLog, Display, TEXT("DeathAnimMontage"));
		PlayAnimMontage(DeathAnimMontage);
		SetLifeSpan(DeathAnimMontage->CalculateSequenceLength() - 0.5f);
	}
	else
	{
		SetLifeSpan(1.f);
	}
}
