// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/KP_BaseCharacter.h"
#include "Components/KP_CharacterMovementComponent.h"
#include "Components/KP_HealthComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

AKP_BaseCharacter::AKP_BaseCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UKP_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent-> SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UKP_HealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

void AKP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AKP_BaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AKP_BaseCharacter::OnHealthChanged);

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

	PlayerInputComponent->BindAxis("MoveForward", this, &AKP_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKP_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AKP_BaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AKP_BaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKP_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("Fight", IE_Pressed, this, &AKP_BaseCharacter::Fight);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AKP_BaseCharacter::Block);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKP_BaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AKP_BaseCharacter::OnStopRunning);
}

bool AKP_BaseCharacter::IsRunning() const
{
	return bWantsToRun && !GetVelocity().IsZero();
}

float AKP_BaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AKP_BaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

	UE_LOG(BaseCharacterLog, Display, TEXT("On Ground Landed %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("Final Damage %f"), FinalDamage);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AKP_BaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AKP_BaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AKP_BaseCharacter::OnStartRunning()
{
	bWantsToRun = true;
}

void AKP_BaseCharacter::OnStopRunning()
{
	bWantsToRun = false;
}

void AKP_BaseCharacter::Fight()
{
	
}

void AKP_BaseCharacter::Block()
{
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
}

void AKP_BaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


