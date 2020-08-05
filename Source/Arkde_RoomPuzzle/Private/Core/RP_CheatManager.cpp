// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_CheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "RP_Character.h"

void URP_CheatManager::RP_UltimateReady()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		ARP_Character* PlayerCharacter = Cast<ARP_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
		{
			PlayerCharacter->GainUltimateXP(10000);
			UE_LOG(LogTemp, Warning, TEXT("Cheat Activated: Ultimate Ready!"));
		}
	}
}

void URP_CheatManager::RP_UltimateXP(float XPGained)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		ARP_Character* PlayerCharacter = Cast<ARP_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter) && PlayerCharacter->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
		{
			PlayerCharacter->GainUltimateXP(XPGained);
			UE_LOG(LogTemp, Warning, TEXT("Cheat Activated: Ultimate XP: %f!"), XPGained);
		}
	}
}
