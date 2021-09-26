// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathWall.h"

// Sets default values
ADeathWall::ADeathWall()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TailMesh"));
	SetRootComponent(StaticMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMesh->SetStaticMesh(Mesh.Object);
}

// Called when the game starts or when spawned
void ADeathWall::BeginPlay()
{
	Super::BeginPlay();
	
}

