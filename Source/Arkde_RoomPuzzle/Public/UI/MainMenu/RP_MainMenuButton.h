// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "RP_MainMenuButton.generated.h"

UENUM()
enum class ERP_ButtonStyleType : uint8
{
	ButtonStyleType_Mouse			UMETA(DisplayName = "Selected by Mouse"),
	ButtonStyleType_KeySelected		UMETA(DisplayName = "Selected by Keyboard"),
	ButtonStyleType_KeyNotSelected	UMETA(DisplayName = "Not Selected by Keyboard")
};

UCLASS()
class ARKDE_ROOMPUZZLE_API URP_MainMenuButton : public UButton
{
	GENERATED_BODY()

public: 

	URP_MainMenuButton();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu Button")
	float CheckFocusRate;

	FTimerHandle TimerHandle_CheckFocus;

protected:

	UFUNCTION(BlueprintCallable, Category = "Main Menu Button")
	void Start();

	void CheckFocus();

	void SetButtonStyle(ERP_ButtonStyleType NewStyleType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Main Menu Button")
	void BP_SetButtonStyle(ERP_ButtonStyleType NewStyleType);
};
