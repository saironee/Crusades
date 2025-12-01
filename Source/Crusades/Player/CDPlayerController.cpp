// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CDPlayerController.h"

#include "UI/CDUserWidget.h"
#include "UI/CDMainWidget.h"

ACDPlayerController::ACDPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCDMainWidget> CDMainWidgetClassRef(TEXT("/Game/Blueprint/UI/WBP_MainWidget.WBP_MainWidget_C"));
	if (CDMainWidgetClassRef.Succeeded())
		HUDClass = CDMainWidgetClassRef.Class;
		
}

void ACDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDClass)
	{
		CDHUDWidget = CreateWidget<UCDUserWidget>(this, HUDClass);
		if (CDHUDWidget)
			CDHUDWidget->AddToViewport(0);
	}
}
