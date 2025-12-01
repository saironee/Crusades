// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CDInventoryWidget.h"

#include <iterator>

#include "Blueprint/WidgetTree.h"
#include "Character/CDFatherCharacter.h"
#include "Components/Image.h"
#include "CustomComponents/CDInventoryComponent.h"
#include "Actor/Item/CDBaseItem.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UCDInventoryWidget::UCDInventoryWidget()
{
	
}

void UCDInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ACDFatherCharacter* OwnerCharacter = Cast<ACDFatherCharacter>(GetOwningPlayerPawn()))
	{
		OwnerCharacter->OnMouseInputMoved.BindUObject(this, &UCDInventoryWidget::SetMouseMoveVector);
		OwnerCharacter->OnInventoryOpenClose.BindUObject(this, &UCDInventoryWidget::SetUIVisiblity);

		if (UCDInventoryComponent* InvComp = Cast<UCDInventoryComponent>(OwnerCharacter->GetComponentByClass(UCDInventoryComponent::StaticClass())))
		{
			InvComp->OnInventoryChanged.AddUObject(this, &UCDInventoryWidget::InventoryChange);
		}
	}
}

void UCDInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float MouseAngle = FMath::Atan2(MouseMoveVector.Y, MouseMoveVector.X) * (360 / (PI * 2));
	
}

void UCDInventoryWidget::SetUIVisiblity(bool bOpen)
{
	UE_LOG(LogTemp, Display, TEXT("SetUIVisiblity"));
	
	if (bOpen)
		this->SetVisibility(ESlateVisibility::Visible);
	else
		this->SetVisibility(ESlateVisibility::Hidden);
}

void UCDInventoryWidget::InventoryChange(TArray<ACDBaseItem*> NewInvArr, uint32 NewCurrentItemNum)
{
	UE_LOG(LogTemp, Warning, TEXT("InventoryChange - Circular Layout"));

}

