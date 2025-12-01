// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CDFatherAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CDFatherCharacter.h"

UCDFatherAnimInstance::UCDFatherAnimInstance() : bIsGround(true)
{
}

void UCDFatherAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACDFatherCharacter>(GetOwningActor());
}

void UCDFatherAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter)
	{
		FVector Velocity = OwnerCharacter->GetVelocity();
		FRotator Rotation = OwnerCharacter->GetActorRotation();
		
		FVector LocalVelocity = Rotation.UnrotateVector(Velocity);

		ForwardSpeed = LocalVelocity.X;
		RightSpeed = LocalVelocity.Y;

		bIsGround = !OwnerCharacter->GetCharacterMovement()->IsFalling();

		bIsOpenInv = OwnerCharacter->GetCurrentMode() == EFatherMode::Inventory;
	}
}
