// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Enum/FatherMode.h"
#include "AnimNotifyState_FatherModeChange.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API UAnimNotifyState_FatherModeChange : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	class IInterface_FatherModeChange* IFatherModeChange;

public:	
	UPROPERTY(EditAnywhere)
	EFatherMode NewMode;
};
