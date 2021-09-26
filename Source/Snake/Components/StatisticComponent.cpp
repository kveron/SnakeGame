// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Snake/SnakeGameInstance.h"
#include "Snake/SnakeGameModeBase.h"

// Sets default values for this component's properties
UStatisticComponent::UStatisticComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatisticComponent::BeginPlay()
{
	Super::BeginPlay();

	StartTime = FDateTime::Now();
	Cast<ASnakeGameModeBase>(UGameplayStatics::GetGameMode(this))->GameOverEvent.AddDynamic(this, &UStatisticComponent::SaveData);
	// ...
}


// Called every frame
void UStatisticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PlayedTime = FDateTime::Now() - StartTime;
	// ...
}


float UStatisticComponent::GetPoints()
{
	return Points;
}

void UStatisticComponent::AddPoints(const float Value)
{
	Points += Value;
}

void UStatisticComponent::SaveData()
{
	USnakeGameInstance* SnakeGameInstance = Cast<USnakeGameInstance>(UGameplayStatics::GetGameInstance(this));
	SnakeGameInstance->DataSet.Emplace(FSnakeSaveData(Points, PlayedTime));
	SnakeGameInstance->DataSet.Sort([](const FSnakeSaveData& A, const FSnakeSaveData& B){
	return A.PlayerPoints > B.PlayerPoints;
	});
}