// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Pickme.generated.h"


/*
 *	무조건 플레이어만 사용할 것!!!!!!!!!!1
 */

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Pickme : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRUSADES_API IInterface_Pickme
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Pickme(const FString& Coment, class ACDBaseItem* Item) = 0;
};
