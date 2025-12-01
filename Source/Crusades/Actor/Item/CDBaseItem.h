// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interface_ItemDudeClear.h"
#include "CDBaseItem.generated.h"

UCLASS()
class CRUSADES_API ACDBaseItem : public AActor,
	public IInterface_ItemDudeClear
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDBaseItem();

	virtual void DudeClear() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	class UNiagaraComponent* NiagaraComp;
	
	UPROPERTY()
	class UNiagaraSystem* GlitterParticle;

	UPROPERTY(EditAnywhere)
	USceneComponent* ParticleSpawnLocation;
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxTrigger;

public:
	UTexture2D* GetIconTexture() { return IconTexture; }

protected:
	UFUNCTION()
	virtual void BeginOverlapBoxTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void EndOverlapBoxTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	FString Coment;

	float MeshRotationSpeed = 2.f;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* IconTexture;
};