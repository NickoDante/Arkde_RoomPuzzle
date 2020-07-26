// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RP_LevelMusic.generated.h"

class UBillboardComponent;
class UAudioComponent;
class ARP_GameMode;

UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_LevelMusic : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* MusicBillboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* MusicAudioComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "References")
	ARP_GameMode* GameModeReference;

public:	

	// Sets default values for this actor's properties
	ARP_LevelMusic();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StopLevelMusic();
};
