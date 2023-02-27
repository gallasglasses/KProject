// Fill out your copyright notice in the Description page of Project Settings.

//custom h
#include "AI/KP_AICharacter.h"
#include "AI/KP_AIController.h"

#include "Components/KP_AIMovementComponent.h"
#include "Components/KP_HealthComponent.h"
#include "Components/KP_StaminaComponent.h"
#include "Components/KP_ManaComponent.h"
#include "Components/KP_WeaponComponent.h"

#include "UI/KP_HealthBarWidget.h"

#include "Weapons/KP_Dagger.h"

//ue h
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(AICharacterLog, All, All);

AKP_AICharacter::AKP_AICharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UKP_AIMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AKP_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->TargetArmLength = 350.0f;
	SpringArmComponent->SocketOffset = FVector(-20.0f, 0.0f, 200.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));

	HealthComponent = CreateDefaultSubobject<UKP_HealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	HealthTextComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->bOwnerNoSee = false;
	//HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HealthWidgetComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	HealthWidgetComponent->SetDrawAtDesiredSize(true);

	WeaponComponent = CreateDefaultSubobject<UKP_WeaponComponent>("WeaponComponent");
}

void AKP_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(StaminaComponent);
	check(ManaComponent);
	check(HealthTextComponent);
	check(HealthWidgetComponent)
	check(GetCharacterMovement());
	check(WeaponComponent);

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AKP_AICharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AKP_AICharacter::OnHealthChanged);

	WeaponComponent->OnWantToStartThrowing.AddUObject(this, &AKP_AICharacter::OnStartAttacking);
	WeaponComponent->OnWantToStopThrowing.AddUObject(this, &AKP_AICharacter::OnStopAttacking);

	LandedDelegate.AddDynamic(this, &AKP_AICharacter::OnGroundLanded);
	const auto CharacterController = Cast<AKP_AIController>(GetController());
	CharacterController->OnFindEnemy.AddUObject(this, &AKP_AICharacter::OnFindEnemy);
}

void AKP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKP_AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AKP_AICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKP_AICharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AKP_AICharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AKP_AICharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKP_AICharacter::Jump);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &AKP_AICharacter::MeleeAttack);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AKP_AICharacter::Block);
}

bool AKP_AICharacter::IsAttacking() const
{
	return bIsAttacking;
}

bool AKP_AICharacter::IsThrowingWeapon() const
{
	return bIsThrowingWeapon;
}

void AKP_AICharacter::SetThrowing(bool bIsActing)
{
	bIsThrowingWeapon = bIsActing;

	if (bIsThrowingWeapon)
	{
		UE_LOG(AICharacterLog, Display, TEXT("Throwing Weapon"));
		WeaponComponent->ThrowDagger();
	}
}

float AKP_AICharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AKP_AICharacter::OnStartAttacking()
{
	UE_LOG(AICharacterLog, Display, TEXT("On Melee Attack"));
	MeleeAttack();
}

void AKP_AICharacter::OnStopAttacking()
{
	UE_LOG(AICharacterLog, Display, TEXT("On Stop Attack"));
	StopAttack();
}

FVector AKP_AICharacter::GetEnemyLocation()
{
	return EnemyLocation;
}

void AKP_AICharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	UE_LOG(AICharacterLog, Display, TEXT("On Ground Landed %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(AICharacterLog, Display, TEXT("Final Damage %f"), FinalDamage);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AKP_AICharacter::MoveForward(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AKP_AICharacter::MoveRight(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AKP_AICharacter::Block()
{
	
}

void AKP_AICharacter::OnDeath()
{
	UE_LOG(AICharacterLog, Display, TEXT("%s, You are dead"), *GetName());

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement(); //UCharacterMovementComponent * GetCharacterMovement() const
	SetLifeSpan(5.f);
}

void AKP_AICharacter::OnHealthChanged(float Health, float HealthDelta)
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

void AKP_AICharacter::OnFindEnemy(FVector Location)
{
	EnemyLocation = Location;
}

void AKP_AICharacter::MeleeAttack()
{
	if (bIsAttacking)
	{
		bIsComboAttack = true;

		UE_LOG(AICharacterLog, Display, TEXT("Attacking yet and save"));
	}
	else
	{
		bIsAttacking = true;
		ChooseComboAnimMontage();
		UE_LOG(AICharacterLog, Display, TEXT("Attacking now"));
	}
}

void AKP_AICharacter::ChooseComboAnimMontage()
{
	switch (ComboAttackCount)
	{
	case 0:
		OnPlayAnimMontage(0);
		ComboAttackCount = 1;
		break;
	case 1:
		OnPlayAnimMontage(1);
		ComboAttackCount = 2;
		break;
	case 2:
		OnPlayAnimMontage(2);
		ComboAttackCount = 0;
		break;
	default:
		break;
	}
}

void AKP_AICharacter::OnPlayAnimMontage(int8 Count)
{
	if (bIsAttacking)
	{
		PlayAnimMontage(AttackAnimMontages[Count]);
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKP_AICharacter::ComboAttackSave, AttackAnimMontages[Count]->CalculateSequenceLength(), false);
		UE_LOG(AICharacterLog, Display, TEXT("Play Attack %d"), Count);
	}
}

void AKP_AICharacter::ComboAttackSave()
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

void AKP_AICharacter::ResetCombo()
{
	ComboAttackCount = 0;
	bIsComboAttack = false;
	StopAttack();
	UE_LOG(AICharacterLog, Display, TEXT("Reset Combo"));
}

void AKP_AICharacter::StopAttack()
{
	bIsAttacking = false;
	bIsDamageDone = false;
	UE_LOG(AICharacterLog, Display, TEXT("Stop Attack"));
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}