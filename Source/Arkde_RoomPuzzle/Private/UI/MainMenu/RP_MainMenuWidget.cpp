// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Core/RP_GameInstance.h"

void URP_MainMenuWidget::NewGame()
{
	BP_NewGame();

	URP_GameInstance* GameInstanceReference = Cast<URP_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->ResetData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void URP_MainMenuWidget::ContinueGame()
{
	BP_Continue();

	URP_GameInstance* GameInstanceReference = Cast<URP_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference))
	{
		GameInstanceReference->LoadData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void URP_MainMenuWidget::QuitGame()
{
	BP_QuitGame();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}
