// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameModeBase.h"

#include "SnakePawn/SnakeHead.h"
#include "AppleActor/Apple.h"
#include "Kismet/GameplayStatics.h"
#include "Math/TransformCalculus3D.h"

ASnakeGameModeBase::ASnakeGameModeBase()
{
	DefaultPawnClass = ASnakeHead::StaticClass();
	
	AppleSpawner = CreateDefaultSubobject<UAppleSpawner>(TEXT("AppleSpawner"));
	StatisticComponent = CreateDefaultSubobject<UStatisticComponent>(TEXT("StatisticComponent"));
}

void ASnakeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	ASnakeHead* SnakeHead = GetWorld()->SpawnActor<ASnakeHead>(ASnakeHead::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, FActorSpawnParameters());
	UGameplayStatics::GetPlayerController(this,0)->Possess(SnakeHead);

	AppleSpawner->SpawnApple();
}

void ASnakeGameModeBase::EndGame()
{
	GameOverEvent.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("GAMEOVER"));
}
