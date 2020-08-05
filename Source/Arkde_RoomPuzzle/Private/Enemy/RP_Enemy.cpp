// Fill out your copyright notice in the Description page of Project Settings.

#include "RP_Enemy.h"
#include "RP_Character.h"
#include "Weapons/RP_Rifle.h"
#include "Components/RP_HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Items/RP_Item.h"
#include "AIModule/Classes/Perception/AISense_Damage.h"
#include "Enemy/Controller/RP_AIController.h"
#include "Core/RP_GameInstance.h"
#include "Components/WidgetComponent.h"
#include "UI/Enemy/RP_EnemyHealthBar.h"
#include "Core/RP_GameMode.h"

ARP_Enemy::ARP_Enemy()
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 20.0f;

	LootProbability = 100.0f;

	WidgetHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHealthBarComponent"));
	WidgetHealthBarComponent->SetupAttachment(RootComponent);
}

void ARP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	MyAIController = Cast<ARP_AIController>(GetController());

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &ARP_Enemy::HealthChanged);
	HealthComponent->OnDeadDelegate.AddDynamic(this, &ARP_Enemy::GiveXP);

	UUserWidget* WidgetObject = WidgetHealthBarComponent->GetUserWidgetObject();
	if (IsValid(WidgetObject))
	{
		EnemyHealthBar = Cast<URP_EnemyHealthBar>(WidgetObject);
		if (IsValid(EnemyHealthBar))
		{
			HealthComponent->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBar, &URP_EnemyHealthBar::UpdateHealth);
			HideHealthBar();
		}
	}
}

void ARP_Enemy::GiveXP(AActor* DamageCauser)
{
	ARP_Character* PossiblePlayer = Cast<ARP_Character>(DamageCauser);
	if (IsValid(PossiblePlayer) && PossiblePlayer->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
	{
		PossiblePlayer->GainUltimateXP(XPValue);
		TrySpawnLoot();
	}

	ARP_Rifle* PossibleRifle = Cast<ARP_Rifle>(DamageCauser);
	if(IsValid(PossibleRifle))
	{
		ARP_Character* RifleOwner = Cast<ARP_Character>(PossibleRifle->GetOwner());
		if (IsValid(RifleOwner) && RifleOwner->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
		{
			RifleOwner->GainUltimateXP(XPValue);
			TrySpawnLoot();
		}
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BP_GiveXP(DamageCauser);
}

bool ARP_Enemy::TrySpawnLoot()
{
	if (!IsValid(LootItemClass))
	{
		return false;
	}

	const float SelectedProbability = FMath::RandRange(0.0f, 100.0f);
	if (SelectedProbability <= LootProbability)
	{
		FActorSpawnParameters SpawnParameter;
		SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ARP_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameter);
	}

	return true;
}

void ARP_Enemy::HealthChanged(URP_HealthComponent* CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!IsValid(MyAIController))
	{
		return;
	}

	if (bIsShowingHealthBar)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideHealthBar);
	}
	else
	{
		ShowHealthBar();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideHealthBar, this, &ARP_Enemy::HideHealthBar, 1.0f, false);

	if (CurrentHealthComponent->IsDead())
	{
		MyAIController->DeactivateAIPerception();
		MyAIController->UnPossess();

		if (IsValid(GameInstanceReference))
		{
			GameInstanceReference->AddEnemyDefeatedToCounter();
		}

		SetAlert(false);

		HideHealthBar();
	}
	else
	{
		ARP_Rifle* Rifle = Cast<ARP_Rifle>(DamageCauser);
		if (IsValid(Rifle))
		{
			AActor* RifleOwner = Rifle->GetOwner();
			MyAIController->SetReceiveDamage(true);
			UAISense_Damage::ReportDamageEvent(GetWorld(), this, RifleOwner, Damage, RifleOwner->GetActorLocation(), FVector::ZeroVector);
		}
	}
}

void ARP_Enemy::ShowHealthBar()
{
	bIsShowingHealthBar = true;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void ARP_Enemy::HideHealthBar()
{
	bIsShowingHealthBar = false;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void ARP_Enemy::SetAlert(bool bValue)
{
	bIsAlert = bValue;

	if (IsValid(GameModeReference))
	{
		GameModeReference->CheckAlertMode();
	}
}
