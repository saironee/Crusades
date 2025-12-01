// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CDBaseGameMode.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"

ACDBaseGameMode::ACDBaseGameMode()
{
	
}

void ACDBaseGameMode::BeginPlay()
{
	// if (GEngine)
	// {
	// 	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	// 	if (Settings)
	// 	{
	// 		Settings->SetScreenResolution(FIntPoint(640, 480));
	// 		Settings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	// 		Settings->ApplySettings(false);
	// 	}
	// }
}

