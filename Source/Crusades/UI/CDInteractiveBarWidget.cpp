// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CDInteractiveBarWidget.h"

#include "Actor/Item/CDBaseItem.h"
#include "Character/CDFatherCharacter.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "CustomComponents/CDInventoryComponent.h"
#include "Components/Image.h"

UCDInteractiveBarWidget::UCDInteractiveBarWidget()
{
}

void UCDInteractiveBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ACDFatherCharacter* OwningChar = Cast<ACDFatherCharacter>(GetOwningPlayerPawn()))
	{
		OwningChar->OnDialoguebarMessage.AddUObject(this, &UCDInteractiveBarWidget::HideShowWidget);
	}

	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCDInteractiveBarWidget::HideShowWidget(const FString& Message)
{
	if (Message.TrimStartAndEnd().IsEmpty())
		CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		CanvasPanel->SetVisibility(ESlateVisibility::Visible);
		Coment->SetText(FText::FromString(Message));
	}
}