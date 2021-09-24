// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Math/TransformCalculus3D.h"
#include "SnakePawn/SnakeHead.h"

ASnakeGameModeBase::ASnakeGameModeBase():
PlayerRecoverTime(3)
{
	DefaultPawnClass = ASnakeHead::StaticClass();
	//EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));

	//HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthComponent"));
}

void ASnakeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	const FTransform SnakeTransform = FTransform(FVector::ZeroVector);
	ASnakeHead* SnakeHead = GetWorld()->SpawnActor<ASnakeHead>(ASnakeHead::StaticClass(), SnakeTransform, FActorSpawnParameters());
	UGameplayStatics::GetPlayerController(this,0)->Possess(SnakeHead);
	//HealthsComponent->HealthsEndedEvent.AddDynamic(this, &ASnakeGameModeBase::EndGame);
	//PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	//PlayerPawn->PawnDamagedEvent.AddDynamic(this, &ASnakeGameModeBase::ExplodePawn);
}

void ASnakeGameModeBase::ExplodePawn_Implementation()
{
	//PlayerPawn->ExplodePawn();
	//HealthsComponent->ChangeHealths(-1);
	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &ASnakeGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void ASnakeGameModeBase::RecoverPawn_Implementation()
{
	//PlayerPawn->RecoverPawn();
}

void ASnakeGameModeBase::EndGame()
{
	GameOverEvent.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("GAMEOVER"));
}
