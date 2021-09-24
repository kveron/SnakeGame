// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class SNAKE_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ASnakeGameModeBase();
	virtual void BeginPlay() override;
	protected:
	FTimerHandle RecoverTimer;

	UFUNCTION(BlueprintNativeEvent,Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category="Healths")
	void RecoverPawn();
	void RecoverPawn_Implementation();
	
	public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemies")
	//UEnemySpawnController* EnemySpawnController;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game Health")
	//UGameHealthComponent* HealthsComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOverEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	//UPROPERTY(BlueprintReadOnly, Category = "Game")
	//APlayerPawn* PlayerPawn;
	
};
