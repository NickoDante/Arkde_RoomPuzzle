// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GrenadeLauncher.h"
#include "Weapons/RP_Projectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ARP_GrenadeLauncher::ARP_GrenadeLauncher()
{
	MuzzleSocketName = "SCK_Muzzle";
}

void ARP_GrenadeLauncher::StartAction()
{
	Super::StartAction();

	if(IsValid(CurrentOwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);

			ARP_Projectile* CurrentProjectile = GetWorld()->SpawnActor<ARP_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
			if (CurrentProjectile)
			{
				CurrentProjectile->SetDamage(Damage);
				CurrentProjectile->SetDamageType(DamageType);
			}
		}
	}
}

void ARP_GrenadeLauncher::StopAction()
{
	Super::StopAction();
}
