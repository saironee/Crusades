// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CDFatherAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUSADES_API UCDFatherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCDFatherAnimInstance();

protected:
	virtual void NativeBeginPlay() override;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInsValue")
	float ForwardSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInsValue")
	float RightSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInsValue")
	uint8 bIsGround : 1;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInsValue")
	uint8 bIsOpenInv : 1;

private:
	UPROPERTY()
	class ACDFatherCharacter* OwnerCharacter;
};
