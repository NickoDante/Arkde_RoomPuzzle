// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GameMode.h"
#include "RP_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework\PawnMovementComponent.h"

void ARP_GameMode::Victory(ARP_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void ARP_GameMode::GameOver(ARP_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Character->DetachFromControllerPendingDestroy();
	Character->SetLifeSpan(5.0f);

	BP_GameOver(Character);
}
