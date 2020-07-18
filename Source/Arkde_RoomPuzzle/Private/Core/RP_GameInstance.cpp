// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/RP_SaveGame.h"

URP_GameInstance::URP_GameInstance()
{
	SaveSlotName = "RP_SaveData";
}

void URP_GameInstance::AddEnemyDefeatedToCounter()
{
	EnemiesDefeatedCounter++;
	OnEnemyKilledDelegate.Broadcast(EnemiesDefeatedCounter);
	BP_AddEnemyDefeatedToCounter();
}

void URP_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(URP_SaveGame::StaticClass());
	}

	if (IsValid(SaveGameObject))
	{
		URP_SaveGame* SaveFile = Cast<URP_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			SaveFile->SetEnemiesDefeatedCounterInfo(EnemiesDefeatedCounter);

			UGameplayStatics::SaveGameToSlot(SaveFile, SaveSlotName, 0);
		}
	}
}

void URP_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);

	if (bExistingData)
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}

	if (IsValid(SaveGameObject))
	{
		URP_SaveGame* SaveFile = Cast<URP_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile))
		{
			EnemiesDefeatedCounter = SaveFile->GetEnemiesDefeatedCounterInfo();
		}
	}

}

void URP_GameInstance::ResetData()
{
	EnemiesDefeatedCounter = 0;
	BP_ResetData();
}
