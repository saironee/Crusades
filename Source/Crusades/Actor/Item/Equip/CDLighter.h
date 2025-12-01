// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/CDSKItem.h"
#include "CDLighter.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API ACDLighter : public ACDSKItem
{
	GENERATED_BODY()

public:
	ACDLighter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
