// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleSpawner.h"

#include "Snake/AppleActor/Apple.h"


// Sets default values for this component's properties
UAppleSpawner::UAppleSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAppleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAppleSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Spawn new apple on field, coordinates must be % 400 (cell size), if cell isn't empty find new coordinates
void UAppleSpawner::SpawnApple()
{
	AApple* NewApple = nullptr;
	while(!NewApple)
	{
		float XCoord = FMath::RandRange(-5600,6000);
		int Round = static_cast<int>(XCoord) % 400;
		XCoord -= Round;
		float YCoord = FMath::RandRange(-5600,6000);
		Round = static_cast<int>(YCoord) % 400;
		YCoord -= Round;
		const FTransform AppleTransform = FTransform(FVector(XCoord,YCoord,0));
		FActorSpawnParameters ActorSpawnParameters = FActorSpawnParameters();
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		NewApple = GetWorld()->SpawnActor<AApple>(AApple::StaticClass(), AppleTransform, ActorSpawnParameters);
	}
}

