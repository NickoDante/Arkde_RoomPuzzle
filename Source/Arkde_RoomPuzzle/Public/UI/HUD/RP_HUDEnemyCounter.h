// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RP_HUDEnemyCounter.generated.h"

class URP_GameInstance;

UCLASS()
class ARKDE_ROOMPUZZLE_API URP_HUDEnemyCounter : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	int EnemiesDefeated;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	URP_GameInstance* GameInstanceReference;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateCounter(int EnemyDefeatedCounter);
};
