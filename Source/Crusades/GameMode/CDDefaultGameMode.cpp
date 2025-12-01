// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CDDefaultGameMode.h"

ACDDefaultGameMode::ACDDefaultGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> DefaultPawnRef(TEXT("/Game/Blueprint/Character/BP_FatherCharacter.BP_FatherCharacter_C"));
	if (DefaultPawnRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnRef.Class;
	}

	ConstructorHelpers::FClassFinder<APlayerController> PCRef(TEXT("/Game/Blueprint/Player/BP_FatherController.BP_FatherController_C"));
	if (PCRef.Succeeded())
		PlayerControllerClass = PCRef.Class;
}