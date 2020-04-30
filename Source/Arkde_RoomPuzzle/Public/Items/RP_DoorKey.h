// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/RP_Item.h"
#include "RP_DoorKey.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_DoorKey : public ARP_Item
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* KeyMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	float XPValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:

	// Sets default values for this actor's properties
	ARP_DoorKey();

public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

protected:

	virtual void Pickup(ARP_Character* PickupCharacter) override;
};
