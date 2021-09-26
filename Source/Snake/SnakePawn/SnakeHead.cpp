// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"

#include "Kismet/GameplayStatics.h"
#include "Snake/SnakeGameModeBase.h"
#include "Snake/AppleActor/Apple.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	
	SnakeHeadCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SnakeHeadCollision"));
	SnakeHeadCollision->SetupAttachment(DefaultSceneRoot);
	SnakeHeadCollision->SetSphereRadius(160.f);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeHeadMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	StaticMesh->SetStaticMesh(SnakeHeadMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> SnakeHeadMaterial(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'"));
	StaticMesh->SetMaterial(0,SnakeHeadMaterial.Object);

	LeftEyeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftEyeStaticMesh"));
	LeftEyeStaticMesh->SetupAttachment(StaticMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeLeftEyeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	LeftEyeStaticMesh->SetStaticMesh(SnakeLeftEyeMesh.Object);
	LeftEyeStaticMesh->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
	LeftEyeStaticMesh->SetRelativeLocation(FVector(90,-60,100));
	
	RightEyeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightEyeStaticMesh"));
	RightEyeStaticMesh->SetupAttachment(StaticMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SnakeRightEyeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	RightEyeStaticMesh->SetStaticMesh(SnakeLeftEyeMesh.Object);
	RightEyeStaticMesh->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
	RightEyeStaticMesh->SetRelativeLocation(FVector(90,40,100));
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(DefaultSceneRoot);
	CameraComponent->SetRelativeLocation(FVector(0,0,7000));
	CameraComponent->SetRelativeRotation(FRotator(-90,180,180));
}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ASnakeHead::OnSnakeOverlap);
	GameModeBase = Cast<ASnakeGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameModeBase->GameOverEvent.AddDynamic(this, &ASnakeHead::SetGameEnded);
	SetNextPosition();
}

void ASnakeHead::OnSnakeOverlap(AActor* OverlapActor, AActor* OtherActor)
{
	if(GameEnded)
		return;
	AApple* Apple = Cast<AApple>(OtherActor);
	if(!Apple)
	{
		GameModeBase->EndGame();
		return;
	}
	GameModeBase->StatisticComponent->AddPoints(1);
	AddTail();
	GameModeBase->AppleSpawner->SpawnApple();
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!GameEnded)
		MoveToNextPosition(DeltaTime);
}

void ASnakeHead::SetGameEnded()
{
	GameEnded = true;
}
// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Left", IE_Pressed,this, &ASnakeHead::MoveLeft);
	PlayerInputComponent->BindAction("Right", IE_Pressed,this, &ASnakeHead::MoveRight);
}

void ASnakeHead::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	PlayerController = Cast<APlayerController>(NewController);
}

void ASnakeHead::MoveLeft()
{
	PlayerDirection = EPlayerDirection::MoveLeft;
}

void ASnakeHead::MoveRight()
{
	PlayerDirection = EPlayerDirection::MoveRight;
}

void ASnakeHead::SetNextPosition()
{
	NextPosition = GetActorLocation() + StaticMesh->GetForwardVector() * 400.f;
	if(Tail.Num() != 0)
		MoveTail();
}

void ASnakeHead::MoveToNextPosition(const float& DeltaTime)
{
	//use Interpolation for imitating snake movement
	const float XCoord = FMath::FInterpConstantTo(GetActorLocation().X,NextPosition.X, DeltaTime, (GetActorLocation() - NextPosition).Size2D() * MovementSpeed);
	const float YCoord = FMath::FInterpConstantTo(GetActorLocation().Y,NextPosition.Y, DeltaTime, (GetActorLocation() - NextPosition).Size2D() * MovementSpeed);
	const FVector NewPosition(XCoord,YCoord,0);
	SetActorLocation(NewPosition);
	if((GetActorLocation() - NextPosition).Size2D() < 10)
	{
		SetActorLocation(NextPosition);
		if(PlayerDirection == EPlayerDirection::MoveForward)
			SetNextPosition();
		else
			RotateSnake(DeltaTime);
	}
}

void ASnakeHead::RotateSnake(const float& DeltaTime)
{
	StaticMesh->SetRelativeRotation(FRotator(StaticMesh->GetRelativeRotation().Pitch, StaticMesh->GetRelativeRotation().Yaw + 90 * PlayerDirection, StaticMesh->GetRelativeRotation().Roll));
	PlayerDirection = EPlayerDirection::MoveForward;
}

void ASnakeHead::AddTail()
{
	ASnakeTail* SnakeTail;
	if(Tail.Num() == 0)
	{
		SnakeTail = GetWorld()->SpawnActor<ASnakeTail>(ASnakeTail::StaticClass(), GetActorLocation() - StaticMesh->GetForwardVector()*400, FRotator::ZeroRotator, FActorSpawnParameters());
		SnakeTail->SetNextPosition(GetActorLocation());
	}
	else
	{
		SnakeTail = GetWorld()->SpawnActor<ASnakeTail>(ASnakeTail::StaticClass(), Tail.Last()->GetActorLocation() - Tail.Last()->GetActorForwardVector()*400, FRotator::ZeroRotator, FActorSpawnParameters());
		SnakeTail->SetNextPosition(Tail.Last()->GetActorLocation());
	}
	Tail.Emplace(SnakeTail);
}

void ASnakeHead::MoveTail()
{
	for(int i = Tail.Num() - 1; i > 0; --i)
		Tail[i]->SetNextPosition(Tail[i-1]->GetActorLocation());
	Tail[0]->SetNextPosition(GetActorLocation());
}
