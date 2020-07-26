// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_LevelMusic.h"
#include "Components/BillboardComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ARP_LevelMusic::ARP_LevelMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MusicBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("MusicBillboardComponent"));
	RootComponent = MusicBillboardComponent;

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
	MusicAudioComponent->SetupAttachment(RootComponent);

	AlertParamName = "Alert";
}

// Called when the game starts or when spawned
void ARP_LevelMusic::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<ARP_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameModeReference))
	{
		GameModeReference->OnVictoryDelegate.AddDynamic(this, &ARP_LevelMusic::StopLevelMusic);
		GameModeReference->OnGameOverDelegate.AddDynamic(this, &ARP_LevelMusic::StopLevelMusic);
		GameModeReference->OnAlertModeChangeDelegate.AddDynamic(this, &ARP_LevelMusic::ChangeLevelMusic);
	}
}

void ARP_LevelMusic::StopLevelMusic()
{
	MusicAudioComponent->Stop();
}

void ARP_LevelMusic::ChangeLevelMusic(bool bIsAlert)
{
	MusicAudioComponent->SetBoolParameter(AlertParamName, bIsAlert);
}
