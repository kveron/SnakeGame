// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/AppleSpawner.h"
#include "Components/StatisticComponent.h"
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
	
	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemies")
	UAppleSpawner* AppleSpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemies")
	UStatisticComponent* StatisticComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOverEvent;
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();
};
