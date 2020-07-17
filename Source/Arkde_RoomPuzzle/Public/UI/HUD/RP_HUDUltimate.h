// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RP_HUDUltimate.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API URP_HUDUltimate : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float UltimatePercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor UltimateColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor UltimateEnabledColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor UltimateDisabledColor;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateUltimateValue(float CurrentUltimateXP, float MaxUltimateXP);

	UFUNCTION()
	void UpdateUltimateStatus(bool bIsAvailable);
};
