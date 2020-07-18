// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HUDEnemyCounter.h"
#include "Core/RP_GameInstance.h"

void URP_HUDEnemyCounter::InitializeWidget()
{
	GameInstanceReference = Cast<URP_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->OnEnemyKilledDelegate.AddDynamic(this, &URP_HUDEnemyCounter::UpdateCounter);
		UpdateCounter(GameInstanceReference->GetEnemiesDefeatedCounter());
	}
}

void URP_HUDEnemyCounter::UpdateCounter(int EnemyDefeatedCounter)
{
	EnemiesDefeated = EnemyDefeatedCounter;
}
