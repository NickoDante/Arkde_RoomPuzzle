// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RP_HUDObjective.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API URP_HUDObjective : public UUserWidget
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	bool bIsCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FName ObjectiveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor CurrentColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor CompletedColor;

public:

	void ObjectiveCompleted();

};
