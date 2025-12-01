// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotifyState_FatherModeChange.h"

#include "Interface/Interface_FatherModeChange.h"

void UAnimNotifyState_FatherModeChange::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                    float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	IFatherModeChange = Cast<IInterface_FatherModeChange>(MeshComp->GetOwner());
	if (IFatherModeChange)
	{
		IFatherModeChange->ModeChange(NewMode);
	}
}

void UAnimNotifyState_FatherModeChange::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (IFatherModeChange)
		IFatherModeChange->ModeChange(EFatherMode::None);
}
