// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RP_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API URP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Enemy Data")
	int EnemiesDefeatedCounter;

public: 

	UFUNCTION(BlueprintCallable)
	int GetEnemiesDefeatedCounter() { return EnemiesDefeatedCounter;};

	UFUNCTION(BlueprintCallable)
	void SetEnemiesDefeatedCounter(int NewValue) { EnemiesDefeatedCounter = NewValue; };

	UFUNCTION(BlueprintCallable)
	void AddEnemyDefeatedToCounter();

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AddEnemyDefeatedToCounter();
};
