// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GameInstance.h"

void URP_GameInstance::AddEnemyDefeatedToCounter()
{
	EnemiesDefeatedCounter++;
	BP_AddEnemyDefeatedToCounter();
}
