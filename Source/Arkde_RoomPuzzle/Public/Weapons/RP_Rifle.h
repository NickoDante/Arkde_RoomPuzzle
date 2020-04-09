// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RP_Weapon.h"
#include "RP_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_Rifle : public ARP_Weapon
{
	GENERATED_BODY()
	
protected:

	virtual void StartAction() override;

	virtual void StopAction() override;
};
