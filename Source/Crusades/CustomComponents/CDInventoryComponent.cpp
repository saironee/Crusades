// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/CDInventoryComponent.h"
#include "Actor/Item/CDBaseItem.h"

// Sets default values for this component's properties
UCDInventoryComponent::UCDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCDInventoryComponent::AddItemToInventory(ACDBaseItem* Item)
{
	InventoryArr.Add(Item);
	OnInventoryChanged.Broadcast(InventoryArr, CurrentInventoryNum);
}