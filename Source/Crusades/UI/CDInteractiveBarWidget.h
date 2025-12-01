// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CDUserWidget.h"
#include "CDInteractiveBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API UCDInteractiveBarWidget : public UCDUserWidget
{
	GENERATED_BODY()
public:
	UCDInteractiveBarWidget();

protected:
	virtual void NativeConstruct() override;

protected:
	void HideShowWidget(const FString& Message);

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Coment;
};
