// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RP_AIController.generated.h"

class ARP_Enemy;
class UBehaviorTree;
class UBlackboardComponent;
class UAIPerceptionComponent;

UCLASS()
class ARKDE_ROOMPUZZLE_API ARP_AIController : public AAIController
{
	GENERATED_BODY()

public:

	ARP_AIController();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent; 

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Controller")
	bool bReceivingDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName LoopPathParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName DirectionIndexParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName WaitingTimeParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName CanSeePlayerParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName InvestigatingParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	FName TargetLocationParameterName;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Controller")
	ARP_Enemy* MyEnemy;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Controller")
	UBlackboardComponent* MyBlackBoard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Controller")
	UBehaviorTree* EnemyBehaviorTree;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateSenses(const TArray<AActor*>& UpdatedActors);

public:

	void SetReceiveDamage(bool bNewState) { bReceivingDamage = bNewState; };
};
