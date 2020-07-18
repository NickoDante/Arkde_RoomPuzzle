// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HUDGameState.h"
#include "Core/RP_GameMode.h"

void URP_HUDGameState::InitializeWidget()
{
	GameModeReference = Cast<ARP_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &URP_HUDGameState::OnVictory);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &URP_HUDGameState::OnGameOver);
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void URP_HUDGameState::OnVictory()
{
	GameStateName = VictoryName;
	SetVisibility(ESlateVisibility::Visible);
}

void URP_HUDGameState::OnGameOver()
{
	GameStateName = GameOverName;
	SetVisibility(ESlateVisibility::Visible);
}
