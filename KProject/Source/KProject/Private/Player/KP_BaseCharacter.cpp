// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/KP_BaseCharacter.h"
#include "Components/KP_CharacterAbilitiesComponent.h"
#include "Components/KP_CharacterMovementComponent.h"
#include "Components/KP_HealthComponent.h"
#include "Components/KP_StaminaComponent.h"
#include "Components/KP_ManaComponent.h"
#include "UI/KP_HealthBarWidget.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);


AKP_BaseCharacter::AKP_BaseCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UKP_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->TargetArmLength = 350.0f;
	SpringArmComponent->SocketOffset = FVector(-20.0f, 0.0f, 200.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent-> SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));

	HealthComponent = CreateDefaultSubobject<UKP_HealthComponent>("HealthComponent");
	StaminaComponent = CreateDefaultSubobject<UKP_StaminaComponent>("StaminaComponent");
	ManaComponent = CreateDefaultSubobject<UKP_ManaComponent>("ManaComponent");
	AbilitiesComponent = CreateDefaultSubobject<UKP_CharacterAbilitiesComponent>("AbilitiesComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent()); 
	HealthTextComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	HealthTextComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->bOwnerNoSee = true;
	//HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HealthWidgetComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	HealthWidgetComponent->SetDrawAtDesiredSize(true);

	SwordTriggerHitComponent = CreateDefaultSubobject<UBoxComponent>("SwordTriggerHitComponent");
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	SwordTriggerHitComponent->AttachToComponent(GetMesh(), AttachmentRules, "FX_Sword_Bottom");
	SwordTriggerHitComponent->OnComponentBeginOverlap.AddDynamic(this, &AKP_BaseCharacter::OnOverlapHit);
	SwordTriggerHitComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

void AKP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(StaminaComponent);
	check(ManaComponent);
	check(AbilitiesComponent);
	check(HealthTextComponent);
	check(HealthWidgetComponent)
	check(GetCharacterMovement());
	
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AKP_BaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AKP_BaseCharacter::OnHealthChanged);

	StaminaComponent->OnExhausted.AddUObject(this, &AKP_BaseCharacter::OnExhausted);
	//OnStaminaChanged(StaminaComponent->GetStamina(), 0.0f);

	ManaComponent->OnMuggle.AddUObject(this, &AKP_BaseCharacter::OnMuggle);

	LandedDelegate.AddDynamic(this, &AKP_BaseCharacter::OnGroundLanded);

	//PlayAnimMontage(LevelStartAnimMontage);
}

void AKP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKP_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AKP_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKP_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AKP_BaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AKP_BaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKP_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &AKP_BaseCharacter::MeleeAttack);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AKP_BaseCharacter::Block);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKP_BaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AKP_BaseCharacter::OnStopRunning);
}

bool AKP_BaseCharacter::IsRunning() const
{
	return bWantsToRun && !GetVelocity().IsZero();
}

bool AKP_BaseCharacter::IsAttacking() const
{
	return bIsAttacking;
}

bool AKP_BaseCharacter::IsBlocking() const
{
	return bIsBlocking;
}

float AKP_BaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AKP_BaseCharacter::SetBlockingState(bool BlockingState)
{
	bIsBlocking = BlockingState;
}

void AKP_BaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	UE_LOG(BaseCharacterLog, Display, TEXT("On Ground Landed %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("Final Damage %f"), FinalDamage);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AKP_BaseCharacter::OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking())
	{
		const auto HitActor = SweepResult.GetActor();
		if (!HitActor)
		{
			return;
		}
		if (HitActor == this)
		{
			return;
		}
		UE_LOG(BaseCharacterLog, Display, TEXT("%s, you got damage"), *SweepResult.GetActor()->GetName());
		MakeDamage(SweepResult);
	}
}

void AKP_BaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
	if (bIsRunning)
	{
		OnGiveAnyStamina.Broadcast();
	}
}

void AKP_BaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AKP_BaseCharacter::OnStartRunning()
{
	bWantsToRun = true;
	bIsRunning = true;
}

void AKP_BaseCharacter::OnStopRunning()
{
	bWantsToRun = false;
	bIsRunning = false;
}

void AKP_BaseCharacter::Block()
{
	if (bIsBlocking)
	{
		UE_LOG(BaseCharacterLog, Display, TEXT("Shield is working!"));
	}
	else
	{
		SetBlockingState(true);
		OnGiveAnyMana.Broadcast();
		PlayAnimMontage(BlockAnimMontage);

		AbilitiesComponent->SpawnAbility();
	}

}

void AKP_BaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("%s, You are dead"), *GetName());

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AKP_BaseCharacter::OnExhausted()
{
	bWantsToRun = false;
}

void AKP_BaseCharacter::OnMuggle()
{
	
}

void AKP_BaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

	const auto HealthBarWidget = Cast<UKP_HealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget)
	{
		return;
	}
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
	HealthBarWidget->SetScaleDamage(HealthDelta);
}

//void AKP_BaseCharacter::OnStaminaChanged(float Stamina, float StaminaDelta)
//{
//	
//}

void AKP_BaseCharacter::MakeDamage(const FHitResult& HitResult)
{
	const auto HitActor = HitResult.GetActor();

	if (!bIsDamageDone)
	{
		HitActor->TakeDamage(WeaponDamageAmount, FDamageEvent{}, GetPlayerController(), this);
		bIsDamageDone = true;
	}
}

void AKP_BaseCharacter::MeleeAttack()
{
	if (bIsAttacking)
	{
		bIsComboAttack = true;

		UE_LOG(BaseCharacterLog, Display, TEXT("Attacking yet and save"));
	}
	else
	{
		bIsAttacking = true;
		ChooseComboAnimMontage();
		UE_LOG(BaseCharacterLog, Display, TEXT("Attacking now"));
	}
	/*if (IsAttacking())
	{
		return;
	}
	OnStartAttacking();*/
}

APlayerController* AKP_BaseCharacter::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		return nullptr;
	}
	return Player->GetController<APlayerController>();
}

void AKP_BaseCharacter::OnStartAttacking()
{
	
}

void AKP_BaseCharacter::ChooseComboAnimMontage()
{
	switch (ComboAttackCount)
	{
	case 0:
		OnPlayAnimMontage(0);
		ComboAttackCount = 1;
		RecoveryCount = 0;
		break;
	case 1:
		OnPlayAnimMontage(1);
		ComboAttackCount = 2;
		RecoveryCount = 1;
		break;
	case 2:
		OnPlayAnimMontage(2);
		ComboAttackCount = 3;
		RecoveryCount = 2;
		break;
	case 3:
		OnPlayAnimMontage(3);
		ComboAttackCount = 0;
		RecoveryCount = 3;
		break;
	default:
		break;
	}
}

void AKP_BaseCharacter::OnPlayAnimMontage(int8 Count)
{
	if (bIsAttacking)
	{
		PlayAnimMontage(AttackAnimMontages[Count]);
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKP_BaseCharacter::ComboAttackSave, AttackAnimMontages[Count]->CalculateSequenceLength(), false);
		UE_LOG(BaseCharacterLog, Display, TEXT("Play Attack %d"), Count);
	}
	else 
	{
		PlayAnimMontage(RecoveryAnimMontages[Count]);
		UE_LOG(BaseCharacterLog, Display, TEXT("Play Recovery %d"), Count);
	}
}

void AKP_BaseCharacter::ComboAttackSave()
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

void AKP_BaseCharacter::ResetCombo()
{
	ComboAttackCount = 0;
	bIsComboAttack = false;
	OnStopAttacking();
	UE_LOG(BaseCharacterLog, Display, TEXT("Reset Combo"));
}

void AKP_BaseCharacter::OnStopAttacking()
{
	bIsAttacking = false;
	bIsDamageDone = false;
	UE_LOG(BaseCharacterLog, Display, TEXT("Stop Attack"));
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	switch (RecoveryCount)
	{
	case 0:
		OnPlayAnimMontage(0);
		break;
	case 1:
		OnPlayAnimMontage(1);
		break;
	case 2:
		OnPlayAnimMontage(2);
		break;
	case 3:
		OnPlayAnimMontage(3);
		break;
	default:
		break;
	}
}