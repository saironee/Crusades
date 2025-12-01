#pragma once

#include "CoreMinimal.h"
#include "Crusades/Character/CDBaseCharacter.h"

#include "InputActionValue.h"
#include "Interface/Inteface_InventoryOpenClose.h"
#include "Interface/Interface_Pickme.h"
#include "Enum/FatherMode.h"
#include "Interface/Interface_FatherModeChange.h"
#include "Interface/Interface_PickupItem.h"

#include "CDFatherCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnMouseInputMoved, FVector2D)
DECLARE_DELEGATE_OneParam(FOnInventoryOpenClose, bool)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialoguebarMessage, const FString&)

UCLASS()
class CRUSADES_API ACDFatherCharacter : public ACDBaseCharacter,
	public IInteface_InventoryOpenClose,
	public IInterface_Pickme,
	public IInterface_FatherModeChange,
	public IInterface_PickupItem
{
	GENERATED_BODY()

public:
	ACDFatherCharacter();

public:
	virtual void InventoryOpenClose(bool bOpen) override;
	virtual void Pickme(const FString& Coment, ACDBaseItem* Item) override;
	virtual void ModeChange(EFatherMode NewMode) override;
	virtual void PickupItem() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	virtual void Landed(const FHitResult& Hit) override;

public:
	FOnMouseInputMoved OnMouseInputMoved;
	FOnInventoryOpenClose OnInventoryOpenClose;
	FOnDialoguebarMessage OnDialoguebarMessage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

protected:
	UPROPERTY(VisibleAnywhere)
	class UInputMappingContext* IMCDefault;

	UPROPERTY(VIsibleAnywhere)
	class UInputAction* IAMove;
	UPROPERTY(VIsibleAnywhere)
	UInputAction* IALook;
	UPROPERTY(VisibleAnywhere)
	UInputAction* IARun;
	UPROPERTY(VisibleAnywhere)
	UInputAction* IAViewChange;
	UPROPERTY(VisibleAnywhere)
	UInputAction* IAInventory;
	UPROPERTY(VisibleAnywhere)
	UInputAction* IAInteractive;
	
private:
	void Move(const FInputActionValue& Value);
	void MoveNone(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnStartRun(const FInputActionValue& Value);
	void OnStopRun(const FInputActionValue& Value);
	void ViewChange(const FInputActionValue& Value);
	void Inventory(const FInputActionValue& Value);
	void Interactive(const FInputActionValue& Value);

private:
	EFatherMode CurrentFatherMode;
	
	bool bCanRun = true;
	bool bIsRunning = false;
	bool bCanInteractive = false;
	
	FTimerHandle RunTimerHandle;

	UPROPERTY()
	class ACDBaseItem* DropItem;

#pragma region Camera

	float OriginalTargetArmLength;
	FVector OriginalSocketOffset;
	FVector OriginalSpringArmRV;
	FRotator OriginalSpringArmRR;

	float TargetTargetArmLength;
	FVector TargetSocketOffset = FVector::ZeroVector;
	FVector TargetSpringArmRV = FVector::ZeroVector;
	FRotator TargetSpringArmRR = FRotator::ZeroRotator;
	
	void SetTargetTargetArmLength(const float& Value);
	void SetTargetSocketOffset(const FVector& Value);
	void SetTargetSpringArmRV(const FVector& Value);
	void SetTargetSpringArmRR(const FRotator& Value);

	void RestoreTargetTargetArmLength();
	void RestoreTargetSocketOffset();
	void RestoreTargetSpringArmRV();
	void RestoreTargetSpringArmRR();
#pragma endregion
	
private:
	void NewCharacterMaxWalkSpeed(const float NewSpeed);
	void RollbackSpeed();

	float OriginalSpeed;

public:	
	EFatherMode GetCurrentMode() { return CurrentFatherMode; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCDInventoryComponent* InventoryComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* ItemMidPivot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemMidPivotExtent = 20.f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	UAnimMontage* PickupHighItemMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	UAnimMontage* PickupMidItemMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
	UAnimMontage* PickupDownItemMontage;
};