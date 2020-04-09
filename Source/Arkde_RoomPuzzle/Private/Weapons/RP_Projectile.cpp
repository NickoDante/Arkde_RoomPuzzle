// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARP_Projectile::ARP_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
}

// Called when the game starts or when spawned
void ARP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARP_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARP_Projectile::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

void ARP_Projectile::SetDamageType(TSubclassOf<UDamageType> NewDamageType)
{
	DamageType = NewDamageType;
}

void ARP_Projectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (IsValid(OtherActor))
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, DamageType);
		Destroy();
	}
}

