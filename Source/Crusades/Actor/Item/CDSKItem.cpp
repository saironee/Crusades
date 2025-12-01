// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/CDSKItem.h"

ACDSKItem::ACDSKItem()
{
	SKMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	if (SKMeshComp)
		SKMeshComp->SetupAttachment(RootComponent);
}

void ACDSKItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SKMeshComp->AddRelativeRotation(FRotator(0.f, MeshRotationSpeed, 0.f));
}
