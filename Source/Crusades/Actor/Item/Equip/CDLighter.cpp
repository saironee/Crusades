// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Equip/CDLighter.h"

#include "Components/Image.h"

ACDLighter::ACDLighter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Art/Item/Lighter/Lighter.Lighter"));
	if (MeshRef.Succeeded())
	{
		SKMeshComp->SetSkeletalMesh(MeshRef.Object);
	}

	Coment = FString(TEXT("Press Spacebar"));

	ConstructorHelpers::FObjectFinder<UTexture2D> IconImageRef (TEXT("/Game/Texture/UI/Icon/LighterUI.LighterUI"));
	if (IconImageRef.Succeeded())
		IconTexture = IconImageRef.Object;
}

void ACDLighter::BeginPlay()
{
	Super::BeginPlay();
}

void ACDLighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
