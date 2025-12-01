// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/CDSMItem.h"

ACDSMItem::ACDSMItem()
{
	SMMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	if (SMMeshComp)
		SMMeshComp->SetupAttachment(RootComponent);
}

void ACDSMItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SMMeshComp->AddRelativeRotation(FRotator(0.f, MeshRotationSpeed, 0.f));
}
