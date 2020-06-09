// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_PathActor.h"
#include "Components/BillboardComponent.h"

// Sets default values
ARP_PathActor::ARP_PathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PathBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("PathBillboard"));
	RootComponent = PathBillboardComponent;
}

// Called when the game starts or when spawned
void ARP_PathActor::BeginPlay()
{
	Super::BeginPlay();
	
}
