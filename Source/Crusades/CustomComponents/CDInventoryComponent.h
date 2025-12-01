// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryChanged, const TArray<class ACDBaseItem*>, uint32)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRUSADES_API UCDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCDInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnInventoryChanged OnInventoryChanged;
	
	ACDBaseItem* GetCurrentItem()
	{
		if (InventoryArr.Num() == 0)
			return nullptr;
		
		return InventoryArr[CurrentInventoryNum];
	}

	void AddItemToInventory(ACDBaseItem* Item);

private:
	UPROPERTY()
	TArray<ACDBaseItem*> InventoryArr;

	uint32 CurrentInventoryNum;
};
