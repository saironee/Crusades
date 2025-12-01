// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Interactive.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Interactive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRUSADES_API IInterface_Interactive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interactive(AActor* Caller) = 0;
};
