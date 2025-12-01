// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API ACDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACDPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UCDMainWidget> HUDClass;

	UPROPERTY()
	class UCDUserWidget* CDHUDWidget;
};
