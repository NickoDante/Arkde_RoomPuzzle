// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARP_Rifle::ARP_Rifle()
{
	TraceLenght = 10000.0f;
}

void ARP_Rifle::StartAction()
{
	Super::StartAction();

	AActor* CurrentOwner = GetOwner();
	if (IsValid(CurrentOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;

		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * TraceLenght);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.bTraceComplex = true;

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

		if (bHit)
		{
			// Make damage
			AActor* HitActor = HitResult.GetActor();
			if (IsValid(HitActor))
			{
				UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, HitResult, CurrentOwner->GetInstigatorController(), this, DamageType);
			}
		}

		if (bDrawLineTrace)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0.0f, 1.0f);
		}
	}
}

void ARP_Rifle::StopAction()
{
	Super::StopAction();
}
