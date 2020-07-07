// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RP_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API URP_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void NewGame();

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void QuitGame();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
	void BP_NewGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
	void BP_Continue();

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu")
	void BP_QuitGame();
};
