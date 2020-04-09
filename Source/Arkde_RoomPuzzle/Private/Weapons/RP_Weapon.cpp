// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Weapon.h"

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
}

void ARP_Weapon::StopAction()
{
	BP_StopAction();
}

