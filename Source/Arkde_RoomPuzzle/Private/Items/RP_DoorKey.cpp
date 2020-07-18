// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "RP_Character.h"
#include "Core/RP_GameMode.h"

ARP_DoorKey::ARP_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	XPValue = 40.0f;
	KeyTag = "KeyA";
}

void ARP_DoorKey::Pickup(ARP_Character* PickupCharacter)
{
	Super::Pickup(PickupCharacter);

	if (IsValid(PickupCharacter) && PickupCharacter->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
	{
		if (IsValid(GameModeReference))
		{
			GameModeReference->AddKeyToCharacter(PickupCharacter, KeyTag);
		}

		Destroy();
	}
}
