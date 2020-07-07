// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Character.h"
#include "Arkde_RoomPuzzle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/RP_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/RP_HealthComponent.h"
#include "Core/RP_GameMode.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARP_Character::ARP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	FPSCameraSocketName = "SCK_Camera";
	MeleeSocketName = "SCK_Melee";
	MeleeDamage = 10.0f;
	MaxComboMultiplier = 4.0f;
	CurrentComboMultiplier = 1.0f;
	bCanUseWeapon = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(GetMesh(), FPSCameraSocketName);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<URP_HealthComponent>(TEXT("HealthComponent"));

	bUltimateWithTick = false;
	MaxUltimateXP = 100.0f;
	MaxUltimateDuration = 10.0f;
	UltimateFrequency = 0.5f;

	UltimateWalkSpeed = 1000.0f;
	UltimatePlayRate = 2.0f;
	PlayRate = 1.0f;
	UltimateShotFrequency = 0.25f;

	MainMenuMapName = "MainMenuMap";
}

FVector ARP_Character::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}

	if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

// Called when the game starts or when spawned
void ARP_Character::BeginPlay()
{
	Super::BeginPlay();
	InitializeReferences();
	CreateInitialWeapon();
	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &ARP_Character::MakeMeleeDamage);

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &ARP_Character::OnHealthChange);

	NormalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ARP_Character::InitializeReferences()
{
	if (IsValid(GetMesh()))
	{
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}

	GameModeReference = Cast<ARP_GameMode>(GetWorld()->GetAuthGameMode());
}

void ARP_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void ARP_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void ARP_Character::Jump()
{
	Super::Jump();
}

void ARP_Character::StopJumping()
{
	Super::StopJumping();
}

void ARP_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ARP_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());

		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void ARP_Character::StartWeaponAction()
{
	if (!bCanUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();

		if (bIsUsingUltimate)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AutomaticShoot, CurrentWeapon, &ARP_Weapon::StartAction, UltimateShotFrequency, true);
		}
	}
}

void ARP_Character::StopWeaponAction()
{
	if (!bCanUseWeapon)
	{
		return;
	}

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();

		if (bIsUsingUltimate)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AutomaticShoot);
		}
	}
}

void ARP_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombos)
	{
		return;
	}

	if (bCanMakeCombos)
	{
		if (bIsDoingMelee)
		{
			if (bIsComboEnable)
			{
				if (CurrentComboMultiplier < MaxComboMultiplier)
				{
					CurrentComboMultiplier++;
					SetComboEnable(false);
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
	}

	if (IsValid(MyAnimInstance) && IsValid(MeleeMontage))
	{
		MyAnimInstance->Montage_Play(MeleeMontage, PlayRate);
	}

	SetMeleeState(true);
}

void ARP_Character::StopMelee()
{

}

void ARP_Character::StartUltimate()
{
	if (bCanUseUltimate && !bIsUsingUltimate)
	{
		CurrentUltimateDuration = MaxUltimateDuration;

		bCanUseUltimate = false;

		if (IsValid(MyAnimInstance) && IsValid(UltimateMontage))
		{
			GetCharacterMovement()->MaxWalkSpeed = 0.0f;
			const float StartUltimateMontageDuration = MyAnimInstance->Montage_Play(UltimateMontage);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_BeginUltimateBehaviour, this, &ARP_Character::BeginUltimateBehaviour, StartUltimateMontageDuration, false);
		}
		else
		{
			BeginUltimateBehaviour();
		}

		BP_StartUltimate();
	}
}

void ARP_Character::StopUltimate()
{

}

void ARP_Character::GoToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}

void ARP_Character::MakeMeleeDamage(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor == this)
		{
			return;
		}

		ARP_Character* MeleeTarget = Cast<ARP_Character>(OtherActor);
		if (IsValid(MeleeTarget))
		{
			bool bPlayerAttackingEnemy = GetCharacterType() == ERP_CharacterType::CharacterType_Player && MeleeTarget->GetCharacterType() == ERP_CharacterType::CharacterType_Enemy;
			bool bEnemyAttackingPlayer = GetCharacterType() == ERP_CharacterType::CharacterType_Enemy && MeleeTarget->GetCharacterType() == ERP_CharacterType::CharacterType_Player;

			if (bPlayerAttackingEnemy || bEnemyAttackingPlayer)
			{
				UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
			}
		}
		else
		{
			UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
		}
	}
}

void ARP_Character::OnHealthChange(URP_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HealthComponent->IsDead() && GetCharacterType() == ERP_CharacterType::CharacterType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->GameOver(this);
		}
	}
}

void ARP_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInversion? -value : value);
}

// Called every frame
void ARP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUltimateWithTick && bIsUsingUltimate)
	{
		UpdateUltimateDuration(DeltaTime);
	}
}

// Called to bind functionality to input
void ARP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARP_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARP_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ARP_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARP_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARP_Character::StopJumping);

	PlayerInputComponent->BindAction("WeaponAction", IE_Pressed, this, &ARP_Character::StartWeaponAction);
	PlayerInputComponent->BindAction("WeaponAction", IE_Released, this, &ARP_Character::StopWeaponAction);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &ARP_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &ARP_Character::StopMelee);

	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &ARP_Character::StartUltimate);
	PlayerInputComponent->BindAction("Ultimate", IE_Released, this, &ARP_Character::StopUltimate);

	PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &ARP_Character::GoToMainMenu);
}

void ARP_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool ARP_Character::TryAddHealth(float HealthToAdd)
{
	return HealthComponent->TryAddHealth(HealthToAdd);
}

bool ARP_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void ARP_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}

void ARP_Character::SetMeleeState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanUseWeapon = !NewState;
}

void ARP_Character::SetComboEnable(bool NewState)
{
	bIsComboEnable = NewState;
}

void ARP_Character::ResetCombo()
{
	SetComboEnable(false);
	CurrentComboMultiplier = 1.0f;
}

void ARP_Character::GainUltimateXP(float XPGained)
{
	if (bCanUseUltimate || bIsUsingUltimate)
	{
		return;
	}

	CurrentUltimateXP = FMath::Clamp(CurrentUltimateXP + XPGained, 0.0f, MaxUltimateXP);

	if (CurrentUltimateXP == MaxUltimateXP)
	{
		bCanUseUltimate = true;
	}

	BP_GainUltimateXP(XPGained);
}

void ARP_Character::UpdateUltimateDuration(float Value)
{
	CurrentUltimateDuration = FMath::Clamp(CurrentUltimateDuration - Value, 0.0f, MaxUltimateDuration);
	BP_UpdateUltimateDuration(Value);

	if (CurrentUltimateDuration == 0.0f)
	{
		bIsUsingUltimate = false;

		GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
		PlayRate = 1.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AutomaticShoot);

		if (!bUltimateWithTick) 
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Ultimate);
		}

		BP_StopUltimate();
	}
}

void ARP_Character::UpdateUltimateDurationWithTimer()
{
	UpdateUltimateDuration(UltimateFrequency);
}

void ARP_Character::BeginUltimateBehaviour()
{
	bIsUsingUltimate = true;
	GetCharacterMovement()->MaxWalkSpeed = UltimateWalkSpeed;
	PlayRate = UltimatePlayRate;

	if (!bUltimateWithTick)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Ultimate, this, &ARP_Character::UpdateUltimateDurationWithTimer, UltimateFrequency, true);
	}
}
