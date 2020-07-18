// Fill out your copyright notice in the Description page of Project Settings.

#include "RP_Item.h"
#include "Components/SphereComponent.h"
#include "RP_Character.h"
#include "Core/RP_GameMode.h"

// Sets default values
ARP_Item::ARP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = MainColliderComponent;
}

// Called when the game starts or when spawned
void ARP_Item::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeReference = Cast<ARP_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ARP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARP_Item::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor))
	{
		ARP_Character* OverlappedCharacter = Cast<ARP_Character>(OtherActor);
		if (IsValid(OverlappedCharacter) && OverlappedCharacter->GetCharacterType() == ERP_CharacterType::CharacterType_Player)
		{
			Pickup(OverlappedCharacter);
		}
	}
}

void ARP_Item::Pickup(ARP_Character* PickupCharacter)
{
	BP_Pickup(PickupCharacter);
}

