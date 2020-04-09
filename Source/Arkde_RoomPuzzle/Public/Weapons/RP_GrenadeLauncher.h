// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RP_Weapon.h"
#include "RP_GrenadeLauncher.generated.h"

class ARP_Projectile;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_GrenadeLauncher : public ARP_Weapon
{
	GENERATED_BODY()

public:

	ARP_GrenadeLauncher();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Launcher")
	TSubclassOf<ARP_Projectile> ProjectileClass;
	
protected:

	virtual void StartAction() override;

	virtual void StopAction() override;
};
