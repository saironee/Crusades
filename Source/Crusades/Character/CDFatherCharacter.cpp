#include "Character/CDFatherCharacter.h"

#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomComponents/CDInventoryComponent.h"
#include "Actor/Item/CDBaseItem.h"
#include "Interface/Interface_ItemDudeClear.h"

ACDFatherCharacter::ACDFatherCharacter() : CurrentFatherMode(EFatherMode::None)
{
#pragma region Constructors
	ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Game/Art/Father/Father.Father"));
	if (BodyMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0, 90.f, 0.f));
		GetMesh()->SetRelativeScale3D(FVector(0.63f, 0.63f, 0.63f));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance> ABPRef(TEXT("/Game/Animation/Father/ABP_Father.ABP_Father_C"));
	if (ABPRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABPRef.Class);
	}

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArmComp)
	{
		SpringArmComp->SetupAttachment(GetRootComponent());
	}

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	if (CameraComp)
	{
		CameraComp->SetupAttachment(SpringArmComp);
	}

	ItemMidPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemMid"));
	if (ItemMidPivot)
		ItemMidPivot->SetupAttachment(RootComponent);

	InventoryComp = CreateAbstractDefaultSubobject<UCDInventoryComponent>(TEXT("InventoryComponent"));
	
	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCRef(TEXT("/Game/Input/IMC_FatherDefault.IMC_FatherDefault"));
	if (IMCRef.Succeeded())
	{
		IMCDefault = IMCRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> IAMoveRef(TEXT("/Game/Input/InputAction/IA_Move.IA_Move"));
	if (IAMoveRef.Succeeded())
		IAMove = IAMoveRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IALookRef(TEXT("/Game/Input/InputAction/IA_Look.IA_Look"));
	if (IALookRef.Succeeded())
		IALook = IALookRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IARunRef(TEXT("/Game/Input/InputAction/IA_Run.IA_Run"));
	if (IARunRef.Succeeded())
		IARun = IARunRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IAViewChangeRef(TEXT("/Game/Input/InputAction/IA_ViewChange.IA_ViewChange"));
	if (IAViewChangeRef.Succeeded())
		IAViewChange = IAViewChangeRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IAInventoryRef(TEXT("/Game/Input/InputAction/IA_Inventory.IA_Inventory"));
	if (IAInventoryRef.Succeeded())
		IAInventory = IAInventoryRef.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> IAInteractiveRef(TEXT("/Game/Input/InputAction/IA_Interactive.IA_Interactive"));
	if (IAInteractiveRef.Succeeded())
		IAInteractive = IAInteractiveRef.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> PickupHighItemMontageRef(TEXT("/Game/Art/Father/Animation/AM_Father_Anim_Root_PickupUp.AM_Father_Anim_Root_PickupUp"));
	if (PickupHighItemMontageRef.Succeeded())
		PickupHighItemMontage = PickupHighItemMontageRef.Object;
	
	ConstructorHelpers::FObjectFinder<UAnimMontage> PickupMidItemMontageRef(TEXT("/Game/Art/Father/Animation/AM_Father_Anim_Root_PickupMiddle.AM_Father_Anim_Root_PickupMiddle"));
	if (PickupMidItemMontageRef.Succeeded())
		PickupMidItemMontage = PickupMidItemMontageRef.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> PickDownItemMontageRef(TEXT("/Game/Art/Father/Animation/AM_Father_Anim_Root_PickupDown.AM_Father_Anim_Root_PickupDown"));
	if (PickDownItemMontageRef.Succeeded())
		PickupDownItemMontage = PickDownItemMontageRef.Object;

#pragma endregion

	bUseControllerRotationYaw = true;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 25.f;
	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraRotationLagSpeed = 12.4f;
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	// GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);

	//SpringArmComp->TargetArmLength = 80.f;

	GetCharacterMovement()->AirControl = 0.f;
}

void ACDFatherCharacter::InventoryOpenClose(bool bOpen)
{
	OnInventoryOpenClose.Execute(GetCurrentMode() == EFatherMode::Inventory);
}

void ACDFatherCharacter::Pickme(const FString& Coment, ACDBaseItem* Item)
{
	OnDialoguebarMessage.Broadcast(Coment);

	DropItem = Item;
}

void ACDFatherCharacter::ModeChange(EFatherMode NewMode)
{
	if (NewMode == EFatherMode::None)
		bUseControllerRotationYaw = true;
	else
	{
		bUseControllerRotationYaw = false;

		if (DropItem)
		{
			FRotator CurrentRot = GetActorRotation();
			FVector ToTarget  = DropItem->GetActorLocation() - GetActorLocation();
			float TargetYaw = ToTarget.Rotation().Yaw;

			FRotator NewActorRot(CurrentRot.Pitch, TargetYaw, CurrentRot.Roll);
			SetActorRotation(NewActorRot);
			
			if (Controller)
			{
				FRotator NewControlRot = Controller->GetControlRotation();
				NewControlRot.Yaw = TargetYaw;
				Controller->SetControlRotation(NewControlRot);
			}
		}
	}
	
	CurrentFatherMode = NewMode;
	
}

void ACDFatherCharacter::PickupItem()
{
	if (DropItem)
	{
		InventoryComp->AddItemToInventory(DropItem);

		if (IInterface_ItemDudeClear* ItemDudeClear = Cast<IInterface_ItemDudeClear>(DropItem))
		{
			ItemDudeClear->DudeClear();
		}
	}
}

void ACDFatherCharacter::BeginPlay()
{
	Super::BeginPlay();

	OriginalTargetArmLength = SpringArmComp->TargetArmLength;
	OriginalSocketOffset = SpringArmComp->SocketOffset;
	OriginalSpringArmRV = SpringArmComp->GetRelativeLocation();
	OriginalSpringArmRR = SpringArmComp->GetRelativeRotation();

	TargetTargetArmLength = OriginalTargetArmLength;
	TargetSocketOffset = OriginalSocketOffset;
	TargetSpringArmRV = OriginalSpringArmRV;
	TargetSpringArmRR = OriginalSpringArmRR;

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(IMCDefault, 0);
		}
	}
}

void ACDFatherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArmComp->SocketOffset = FMath::VInterpTo(SpringArmComp->SocketOffset, TargetSocketOffset, DeltaTime, 15.f);
	SpringArmComp->SetRelativeLocation(FMath::VInterpTo(SpringArmComp->GetRelativeLocation(), TargetSpringArmRV, DeltaTime, 15.f));
	SpringArmComp->SetRelativeRotation(FMath::RInterpTo(SpringArmComp->GetRelativeRotation(), TargetSpringArmRR, DeltaTime, 15.f));
	
	if (GetCharacterMovement()->IsFalling() && GetVelocity().Z < 0.f)
	{
		bUseControllerRotationYaw = false;
		
		FVector NewVelocity = GetCharacterMovement()->Velocity;
		NewVelocity.X = 0.f;
		NewVelocity.Y = 0.f;
		GetCharacterMovement()->Velocity = NewVelocity;
	}

	//DrawDebugPoint(GetWorld(), MiddleLocation, 5.0f, FColor::Cyan, false, 1.0f);
}

void ACDFatherCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
}

void ACDFatherCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bUseControllerRotationYaw =true;
}

void ACDFatherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IARun, ETriggerEvent::Triggered, this, &ACDFatherCharacter::OnStartRun);
		EnhancedInputComponent->BindAction(IARun, ETriggerEvent::Completed, this, &ACDFatherCharacter::OnStopRun);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ACDFatherCharacter::Move);
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::None, this, &ACDFatherCharacter::MoveNone);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &ACDFatherCharacter::Look);
		EnhancedInputComponent->BindAction(IAViewChange, ETriggerEvent::Started, this, &ACDFatherCharacter::ViewChange);
		EnhancedInputComponent->BindAction(IAInventory, ETriggerEvent::Started, this, &ACDFatherCharacter::Inventory);
		EnhancedInputComponent->BindAction(IAInteractive, ETriggerEvent::Started, this, &ACDFatherCharacter::Interactive);
	}
}

void ACDFatherCharacter::Move(const FInputActionValue& Value)
{
	if (GetCurrentMode() == EFatherMode::Inventory
		|| GetCurrentMode() == EFatherMode::Acting)
		return;
	
	FVector2D MoveVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveVector.X);
	AddMovementInput(GetActorRightVector(), MoveVector.Y);

	if (MoveVector.X < 0.f)
	{
		NewCharacterMaxWalkSpeed(100.f);
		bCanRun = false;
	}
	else if (MoveVector.Y != 0.f)
	{
		NewCharacterMaxWalkSpeed(250.f);
		bCanRun = false;
	}
	else
	{
		if (!bIsRunning || !bCanRun)
			NewCharacterMaxWalkSpeed(250.f);
		bCanRun = true;
	}
}

void ACDFatherCharacter::MoveNone(const FInputActionValue& Value)
{
	//bUseControllerRotationYaw = false;
}

void ACDFatherCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);

	if (GetCurrentMode() == EFatherMode::Inventory)
	{
		OnMouseInputMoved.Execute(LookVector);
	}
}

void ACDFatherCharacter::OnStartRun(const FInputActionValue& Value)
{
	if (bCanRun)
	{
		NewCharacterMaxWalkSpeed(600.f);
		bIsRunning = true;
		//SpringArmComp->TargetArmLength = 70.f;
	}
}

void ACDFatherCharacter::OnStopRun(const FInputActionValue& Value)
{
	RollbackSpeed();
	bIsRunning = false;
	//SpringArmComp->TargetArmLength = 100.f;
}

void ACDFatherCharacter::ViewChange(const FInputActionValue& Value)
{
	if (GetCurrentMode() == EFatherMode::Inventory)
		return;

	float TempValue;
	
	if (SpringArmComp->SocketOffset.Y > 0)
	{
		TempValue = -50.f;
	}
	else
	{
		TempValue = 50.f;
	}

	SetTargetSocketOffset(FVector(SpringArmComp->TargetOffset.X, TempValue, SpringArmComp->TargetOffset.Z));
}

void ACDFatherCharacter::Inventory(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsFalling() || GetCurrentMode() == EFatherMode::Acting)
		return;
	
	if (GetCurrentMode() == EFatherMode::Inventory)
	{
		CurrentFatherMode = EFatherMode::None;

		SpringArmComp->bUsePawnControlRotation = true;
		bUseControllerRotationYaw = true;

		RestoreTargetSocketOffset();
		RestoreTargetSpringArmRV();
		RestoreTargetSpringArmRR();
		RestoreTargetTargetArmLength();
	}
	else
	{
		CurrentFatherMode = EFatherMode::Inventory;

		SpringArmComp->bUsePawnControlRotation = false;
		bUseControllerRotationYaw = false;
		
		SetTargetSocketOffset(FVector::ZeroVector);
		SetTargetSpringArmRV(FVector(31.f, 0.f, -40.f));
		SetTargetSpringArmRR(FRotator(0.f, -40.f, 0.f));
		SetTargetTargetArmLength(50.f);
	}
}

void ACDFatherCharacter::Interactive(const FInputActionValue& Value)
{
	if (GetCurrentMode() == EFatherMode::Acting)
		return;
	
	if (DropItem)
	{
		if (ItemMidPivot->GetComponentLocation().Z + ItemMidPivotExtent < DropItem->GetActorLocation().Z)
			GetMesh()->GetAnimInstance()->Montage_Play(PickupHighItemMontage);

		else if (ItemMidPivot->GetComponentLocation().Z - ItemMidPivotExtent > DropItem->GetActorLocation().Z)
			GetMesh()->GetAnimInstance()->Montage_Play(PickupDownItemMontage);

		else
			GetMesh()->GetAnimInstance()->Montage_Play(PickupMidItemMontage);
	}
}

#pragma region SpringArm

void ACDFatherCharacter::SetTargetTargetArmLength(const float& Value)
{
	OriginalTargetArmLength = SpringArmComp->TargetArmLength;
	TargetTargetArmLength = Value;
}

void ACDFatherCharacter::SetTargetSocketOffset(const FVector& Value)
{
	OriginalSocketOffset = SpringArmComp->SocketOffset;
	TargetSocketOffset = Value;
}

void ACDFatherCharacter::SetTargetSpringArmRV(const FVector& Value)
{
	OriginalSpringArmRV = SpringArmComp->GetRelativeLocation();
	TargetSpringArmRV = Value;
}

void ACDFatherCharacter::SetTargetSpringArmRR(const FRotator& Value)
{
	OriginalSpringArmRR = SpringArmComp->GetRelativeRotation();
	TargetSpringArmRR = Value;
}

void ACDFatherCharacter::RestoreTargetTargetArmLength()
{
	TargetTargetArmLength = OriginalTargetArmLength;
}

void ACDFatherCharacter::RestoreTargetSocketOffset()
{
	TargetSocketOffset = OriginalSocketOffset;
}

void ACDFatherCharacter::RestoreTargetSpringArmRV()
{
	TargetSpringArmRV = OriginalSpringArmRV;
}

void ACDFatherCharacter::RestoreTargetSpringArmRR()
{
	TargetSocketOffset = OriginalSocketOffset;
}

#pragma endregion

void ACDFatherCharacter::NewCharacterMaxWalkSpeed(const float NewSpeed)
{
	OriginalSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ACDFatherCharacter::RollbackSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
}