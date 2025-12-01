// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CDBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API ACDBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACDBaseGameMode();

protected:
	virtual void BeginPlay() override;
	
};
