// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_PickupItem.h"

#include "Interface/Interface_PickupItem.h"

void UAnimNotify_PickupItem::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (IInterface_PickupItem* PickupItem = Cast<IInterface_PickupItem>(MeshComp->GetOwner()))
	{
		PickupItem->PickupItem();
	}
}
