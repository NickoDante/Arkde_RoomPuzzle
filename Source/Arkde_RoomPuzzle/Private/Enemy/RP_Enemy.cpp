// Fill out your copyright notice in the Description page of Project Settings.

#include "RP_Enemy.h"
#include "RP_Character.h"
#include "Weapons/RP_Rifle.h"
#include "Components/RP_HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Items/RP_Item.h"

ARP_Enemy::ARP_Enemy()
{
	bLoopPath = false;
	DirectionIndex = 1;
	WaitingTimeOnPathPoint = 1.0f;
	XPValue = 20.0f;

	LootProbability = 100.0f;
}

void ARP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeadDelegate.AddDynamic(this, &ARP_Enemy::GiveXP);
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

	float SelectedProbability = FMath::RandRange(0.0f, 100.0f);
	if (SelectedProbability <= LootProbability)
	{
		FActorSpawnParameters SpawnParameter;
		SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ARP_Item>(LootItemClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParameter);
	}

	return true;
}
