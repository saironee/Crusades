// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inteface_InventoryOpenClose.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteface_InventoryOpenClose : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRUSADES_API IInteface_InventoryOpenClose
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InventoryOpenClose(bool bOpen) = 0;
};
