// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_InventoryOpenClose.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API UAnimNotify_InventoryOpenClose : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_InventoryOpenClose();
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bOpen : 1;
};
