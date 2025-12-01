// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_InventoryOpenClose.h"

#include "Interface/Inteface_InventoryOpenClose.h"

UAnimNotify_InventoryOpenClose::UAnimNotify_InventoryOpenClose() : bOpen(false)
{
}

void UAnimNotify_InventoryOpenClose::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (IInteface_InventoryOpenClose* Inventory = Cast<IInteface_InventoryOpenClose>(MeshComp->GetOwner()))
	{
		Inventory->InventoryOpenClose(bOpen);
	}
}
