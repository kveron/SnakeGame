// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"


// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//DefaultSceneRoot->SetupAttachment(GetRootComponent());
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeHeadMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	StaticMesh->SetStaticMesh(SnakeHeadMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> SnakeHeadMaterial(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'"));
	StaticMesh->SetMaterial(0,SnakeHeadMaterial.Object);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(DefaultSceneRoot);
	CameraComponent->SetRelativeLocation(FVector(0,0,1000));
	CameraComponent->SetRelativeRotation(FRotator(-90,0,0));
}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

