// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_GameMode.h"
#include "RP_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RP_SpectatingCamera.h"
#include "Sound/SoundCue.h"
#include "Enemy/RP_Enemy.h"

ARP_GameMode::ARP_GameMode()
{
	MainMenuMapName = "MainMenuMap";
}

void ARP_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSpectatingCameras();

	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARP_Enemy::StaticClass(), EnemyActors);
	for (AActor* EnemyActor : EnemyActors)
	{
		if (!IsValid(EnemyActor))
		{
			continue;
		}

		ARP_Enemy* NewEnemy = Cast<ARP_Enemy>(EnemyActor);
		if (IsValid(NewEnemy))
		{
			LevelEnemies.AddUnique(NewEnemy);
		}
	}
}

void ARP_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARP_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			ARP_SpectatingCamera* SpectatingCamera = Cast<ARP_SpectatingCamera>(SpectatingActor);
			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case ERP_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;
				case ERP_SpectatingCameraType::CameraType_GameOver:
					GameOverCamera = SpectatingCamera;
					break;
				default:
					break;
				}
			}
		}
	}
}

void ARP_GameMode::MoveCameraToSpectatingPoint(ARP_Character* Character, ARP_SpectatingCamera* SpectatingCamera)
{
	if (!IsValid(Character) || !IsValid(SpectatingCamera))
	{
		return;
	}

	AController* CharacterController = Character->GetController();
	if (IsValid(CharacterController))
	{
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);
		if (IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void ARP_GameMode::PlayMusic(USoundCue* MusicCue)
{
	if (!IsValid(MusicCue))
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), MusicCue);
}

void ARP_GameMode::AddKeyToCharacter(ARP_Character* KeyOwner, FName KeyTag)
{
	if (IsValid(KeyOwner))
	{
		OnKeyAddedDelegate.Broadcast(KeyTag);
		KeyOwner->AddKey(KeyTag);
	}
}

void ARP_GameMode::Victory(ARP_Character* Character)
{
	Character->DisableInput(nullptr);

	MoveCameraToSpectatingPoint(Character, VictoryCamera);
	OnVictoryDelegate.Broadcast();

	PlayMusic(VictoryMusic);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &ARP_GameMode::BackToMainMenu, 3.0f, false);

	BP_Victory(Character);
}

void ARP_GameMode::GameOver(ARP_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(5.0f);
	}
	else
	{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(Character, GameOverCamera);
	}

	OnGameOverDelegate.Broadcast();

	PlayMusic(GameOverMusic);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_BackToMainMenu, this, &ARP_GameMode::BackToMainMenu, 8.0f, false);

	BP_GameOver(Character);
}

void ARP_GameMode::BackToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName);
}

void ARP_GameMode::CheckAlertMode()
{
	bool bEnemyInAlertMode = false;

	for (ARP_Enemy* EnemyOnLevel : LevelEnemies)
	{
		if (!IsValid(EnemyOnLevel))
		{
			continue;
		}

		if (EnemyOnLevel->IsAlert())
		{
			bEnemyInAlertMode = true;
			break;
		}
	}

	if (bIsAlertMode != bEnemyInAlertMode)
	{
		bIsAlertMode = bEnemyInAlertMode;
		OnAlertModeChangeDelegate.Broadcast(bIsAlertMode);
	}
}
