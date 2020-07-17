// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HUDUltimate.h"
#include "Kismet/GameplayStatics.h"
#include "RP_Character.h"

void URP_HUDUltimate::InitializeWidget()
{
	UltimateColor = UltimateDisabledColor;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		ARP_Character* PlayerCharacter = Cast<ARP_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->OnUltimateUpdateDelegate.AddDynamic(this, &URP_HUDUltimate::UpdateUltimateValue);
			PlayerCharacter->OnUltimateStatusDelegate.AddDynamic(this, &URP_HUDUltimate::UpdateUltimateStatus);
		}
	}
}

void URP_HUDUltimate::UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP)
{
	UltimatePercent = CurrentUltimateXP / MaxUltimateXP;
}

void URP_HUDUltimate::UpdateUltimateStatus(bool bIsAvailable)
{
	UltimateColor = bIsAvailable ? UltimateEnabledColor : UltimateDisabledColor;
}
