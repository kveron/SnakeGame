// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeTail.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Snake/SnakeGameModeBase.h"
#include "SnakeHead.generated.h"

enum EPlayerDirection
{
	MoveLeft = -1,
	MoveForward = 0,
	MoveRight = 1
};

UCLASS()
class SNAKE_API ASnakeHead : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakeHead();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* SnakeHeadCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* LeftEyeStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* RightEyeStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void OnSnakeOverlap(AActor* OverlapActor, AActor* OtherActor);

	bool GameEnded;
	
	UFUNCTION()
	void SetGameEnded();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	APlayerController* PlayerController;
	
	UPROPERTY(VisibleAnywhere, Category = "Game")
	ASnakeGameModeBase* GameModeBase;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	FVector MovementDirection;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 5.f;
	void MoveLeft();
	void MoveRight();
	EPlayerDirection PlayerDirection = EPlayerDirection::MoveForward;
	void SetNextPosition();
	void MoveToNextPosition(const float& DeltaTime);
	void RotateSnake(const float& DeltaTime);
	FVector NextPosition;
	bool StartRotating;
	float NewRotationAngle;
	
	UFUNCTION(Category = "Game")
	void AddTail();
	TArray <ASnakeTail *> Tail;
	void MoveTail();
};

