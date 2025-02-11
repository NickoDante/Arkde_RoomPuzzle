// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_HealthComponent.h"

// Sets default values for this component's properties
URP_HealthComponent::URP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
}

// Called when the game starts
void URP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	MyOwner = GetOwner();
	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &URP_HealthComponent::TakingDamage);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateInitialHealth, this, &URP_HealthComponent::UpdateInitialHealth, 0.2f, false);
}

void URP_HealthComponent::TakingDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health == 0.0f)
	{
		bIsDead = true;
		OnDeadDelegate.Broadcast(DamageCauser);
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);

	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("My Health is: %s"), *FString::SanitizeFloat(Health));
	}
}

bool URP_HealthComponent::TryAddHealth(float HealthToAdd)
{
	if (bIsDead)
	{
		return false;
	}

	if (Health == MaxHealth)
	{
		return false;
	}

	Health = FMath::Clamp(Health + HealthToAdd, 0.0f, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);

	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("My Health is: %s"), *FString::SanitizeFloat(Health));
	}

	return true;
}

void URP_HealthComponent::UpdateInitialHealth()
{
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
}
