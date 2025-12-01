// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/CDBaseItem.h"
#include "CDSMItem.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API ACDSMItem : public ACDBaseItem
{
	GENERATED_BODY()
public:
	ACDSMItem();

	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SMMeshComp;
};