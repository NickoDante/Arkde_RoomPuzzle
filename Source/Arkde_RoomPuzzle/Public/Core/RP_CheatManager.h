// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "RP_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API URP_CheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public: 

	UFUNCTION(exec)
	void RP_UltimateReady();

	UFUNCTION(exec)
	void RP_UltimateXP(float XPGained);

};
