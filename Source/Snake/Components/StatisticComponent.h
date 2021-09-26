// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatisticComponent.generated.h"

//Keeps main data of game (played time and collected apples) 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNAKE_API UStatisticComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatisticComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	float Points = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetPoints();
	
	UFUNCTION(Category = "Game")
	void AddPoints(float Value);

	UPROPERTY(BlueprintReadOnly, Category = "Time")
	FDateTime StartTime;
	UPROPERTY(BlueprintReadOnly, Category = "Time")
	FTimespan PlayedTime;

	UFUNCTION()
	void SaveData();
};


