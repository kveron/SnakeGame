// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeTail.h"

// Sets default values
ASnakeTail::ASnakeTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TailMesh"));
	SetRootComponent(TailMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeTailMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	TailMesh->SetStaticMesh(SnakeTailMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> SnakeTailMaterial(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'"));
	TailMesh->SetMaterial(0,SnakeTailMaterial.Object);
	TailMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TailCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TailCollision"));
	TailCollision->SetupAttachment(TailMesh);
	TailCollision->SetSphereRadius(60.f);
}

// Called when the game starts or when spawned
void ASnakeTail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToNextPosition(DeltaTime);
}

void ASnakeTail::SetNextPosition(const FVector Next)
{
	NextPosition = Next;
}

void ASnakeTail::MoveToNextPosition(const float& DeltaTime)
{
	const float XCoord = FMath::FInterpConstantTo(GetActorLocation().X,NextPosition.X, DeltaTime, (GetActorLocation() - NextPosition).Size2D() * MovementSpeed);
	const float YCoord = FMath::FInterpConstantTo(GetActorLocation().Y,NextPosition.Y, DeltaTime, (GetActorLocation() - NextPosition).Size2D() * MovementSpeed);
	const FVector NewPosition(XCoord,YCoord,0);
	SetActorLocation(NewPosition);
	if((GetActorLocation() - NextPosition).Size2D() < 10)
		SetActorLocation(NextPosition);
}
