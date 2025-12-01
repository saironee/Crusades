// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CDUserWidget.h"
#include "CDInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API UCDInventoryWidget : public UCDUserWidget
{
	GENERATED_BODY()

public:
	UCDInventoryWidget();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetMouseMoveVector(FVector2D Value) { MouseMoveVector = Value; };
	void SetUIVisiblity(bool bOpen);

protected:
	void InventoryChange(TArray<class ACDBaseItem*> NewInvArr, uint32 NewCurrentItemNum);

private:
	FVector2D MouseMoveVector;

protected:	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

protected:	
	UPROPERTY(VisibleDefaultsOnly)
	TArray<ACDBaseItem*> InvenArr;
};
