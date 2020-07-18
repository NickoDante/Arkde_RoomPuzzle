// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RP_Item.generated.h"

class USphereComponent;
class ARP_Character;
class ARP_GameMode;

UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_Item : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainColliderComponent;

protected:

	UPROPERTY(BlueprintReadOnly)
	ARP_GameMode* GameModeReference;

public:	

	// Sets default values for this actor's properties
	ARP_Item();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(ARP_Character* PickupCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void BP_Pickup(ARP_Character* PickupCharacter);

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
