// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Weapon.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARP_Weapon::ARP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;
}

// Called when the game starts or when spawned
void ARP_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARP_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARP_Weapon::StartAction()
{
	BP_StartAction();
	PlaySound(ShotSound);
}

void ARP_Weapon::StopAction()
{
	BP_StopAction();
}

void ARP_Weapon::SetCharacterOwner(ACharacter * NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		CurrentOwnerCharacter = NewOwner;
	}
}

void ARP_Weapon::PlaySound(USoundCue* SoundCue, bool bIs3D, FVector SoundLocation)
{
	if (!IsValid(SoundCue))
	{
		return;
	}

	if (bIs3D)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, SoundLocation);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
	}
}

