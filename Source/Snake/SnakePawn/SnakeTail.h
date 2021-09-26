// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"

UCLASS()
class SNAKE_API ASnakeTail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeTail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveToNextPosition(const float& DeltaTime);
	FVector NextPosition;
	float MovementSpeed = 5.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TailMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* TailCollision;

	void SetNextPosition(const FVector Next);
};
