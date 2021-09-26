// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"

#include "Snake/SnakePawn/SnakeHead.h"

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ActorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(ActorCollision);
	ActorCollision->SetBoxExtent(FVector(170,170,32));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(ActorCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeHeadMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	StaticMesh->SetStaticMesh(SnakeHeadMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> SnakeHeadMaterial(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01'"));
	StaticMesh->SetMaterial(0,SnakeHeadMaterial.Object);
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AApple::OnAppleOverlap);
}

void AApple::OnAppleOverlap(AActor* OverlapActor, AActor* OtherActor)
{
	ASnakeHead* SnakeHead = Cast<ASnakeHead>(OtherActor);
	if(!SnakeHead) return;
	Destroy();
}
// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

