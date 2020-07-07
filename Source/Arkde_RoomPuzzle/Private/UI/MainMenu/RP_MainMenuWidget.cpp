// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_MainMenuWidget.h"

void URP_MainMenuWidget::NewGame()
{
	BP_NewGame();
}

void URP_MainMenuWidget::ContinueGame()
{
	BP_Continue();
}

void URP_MainMenuWidget::QuitGame()
{
	BP_QuitGame();
}
