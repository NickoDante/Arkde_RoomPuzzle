// Fill out your copyright notice in the Description page of Project Settings.

#include "RP_Bot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RP_Character.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "Components/RP_HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ARP_Bot::ARP_Bot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotMeshComponent"));
	BotMeshComponent->SetCanEverAffectNavigation(false);
	BotMeshComponent->SetSimulatePhysics(true);
	RootComponent = BotMeshComponent;

	HealthComponent = CreateDefaultSubobject<URP_HealthComponent>(TEXT("HealthComponent"));

	MinDistanceToTarget = 100.0f;
	ForceMagnitude = 500.0f;
}

// Called when the game starts or when spawned
void ARP_Bot::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn))
	{
		PlayerCharacter = Cast<ARP_Character>(PlayerPawn);
	}

	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &ARP_Bot::TakingDamage);

	BotMaterial = BotMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BotMeshComponent->GetMaterial(0));

	NextPathPoint = GetNextPathPoint();
}

FVector ARP_Bot::GetNextPathPoint()
{
	if (!IsValid(PlayerCharacter))
	{
		return GetActorLocation();
	}

	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);
	if (NavigationPath->PathPoints.Num() > 1)
	{
		return NavigationPath->PathPoints[1];
	}

	// If Navigation points are less or equal than 1.
	return GetActorLocation();
}

void ARP_Bot::TakingDamage(URP_HealthComponent * CurrentHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (IsValid(BotMaterial))
	{
		BotMaterial->SetScalarParameterValue("Pulse", GetWorld()->TimeSeconds);
	}

	if (CurrentHealthComponent->IsDead())
	{
		Destroy();
	}
}

// Called every frame
void ARP_Bot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();
	
	if (DistanceToTarget <= MinDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;

		BotMeshComponent->AddForce(ForceDirection, NAME_None, true);
	}

	DrawDebugSphere(GetWorld(), NextPathPoint, 30.0f, 15, FColor::Purple, false, 0.0f, 0, 1.0f);
}