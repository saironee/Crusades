// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/CDBaseItem.h"
#include "CDSKItem.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API ACDSKItem : public ACDBaseItem
{
	GENERATED_BODY()

public:
	ACDSKItem();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SKMeshComp;
};
