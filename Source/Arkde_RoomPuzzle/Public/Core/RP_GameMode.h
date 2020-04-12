// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RP_GameMode.generated.h"

class ARP_Character;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public: 

	UFUNCTION()
	void Victory(ARP_Character* Character);

	UFUNCTION()
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory(ARP_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver();
};
