// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HUDObjective.h"

void URP_HUDObjective::ObjectiveCompleted()
{
	bIsCompleted = true;
	CurrentColor = CompletedColor;
}
