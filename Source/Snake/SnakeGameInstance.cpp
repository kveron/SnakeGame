// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameInstance.h"

FSnakeSaveData::FSnakeSaveData()
{
	PlayerPoints = 0;
	PlayerTime = 0;
}

FSnakeSaveData::FSnakeSaveData(const float NewPlayerPoints, const FTimespan NewPlayerTime)
{
	PlayerPoints = NewPlayerPoints;
	PlayerTime = NewPlayerTime;
}

USnakeGameInstance::USnakeGameInstance()
{
	int fps = 60; 
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("t.MaxFPS"));
	CVar->Set(fps);
}
