// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GameMode.h"
#include "RP_Character.h"

void ARP_GameMode::Victory(ARP_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void ARP_GameMode::GameOver()
{
	BP_GameOver();
}
