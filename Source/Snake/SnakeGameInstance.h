// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSnakeSaveData
{
	GENERATED_BODY()
	FSnakeSaveData();
	FSnakeSaveData(const float NewPlayerPoints, const FTimespan NewPlayerTime);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SavedData")
	float PlayerPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SavedData")
	FTimespan PlayerTime;
	
};
UCLASS()
class SNAKE_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	USnakeGameInstance();
	UPROPERTY(BlueprintReadOnly, Category="SavedData")
	TArray<FSnakeSaveData> DataSet;
};
