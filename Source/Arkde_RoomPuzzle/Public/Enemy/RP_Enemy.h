// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RP_Character.h"
#include "RP_Enemy.generated.h"

class ARP_PathActor;

/**
 * 
 */
UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_Enemy : public ARP_Character
{
	GENERATED_BODY()

public: 

	ARP_Enemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	bool bLoopPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	int DirectionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Navigation Path")
	float WaitingTimeOnPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Navigation Path")
	ARP_PathActor* MyPath;
	
};
