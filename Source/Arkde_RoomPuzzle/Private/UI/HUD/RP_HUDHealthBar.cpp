// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HUDHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "RP_Character.h"
#include "Components/RP_HealthComponent.h"

void URP_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		ARP_Character* PlayerCharacter = Cast<ARP_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter))
		{
			URP_HealthComponent* PlayerHealthComponent = PlayerCharacter->GetHealthComponent();
			if (IsValid(PlayerHealthComponent))
			{
				PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &URP_HUDHealthBar::UpdateHealth);
			}
		}
	}
}

void URP_HUDHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);
}
