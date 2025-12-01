// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/CDBaseItem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/Interface_Pickme.h"

// Sets default values
ACDBaseItem::ACDBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	BoxTrigger = CreateAbstractDefaultSubobject<UBoxComponent>("Trigger");
	if (BoxTrigger)
		BoxTrigger->SetupAttachment(RootComponent);

	ParticleSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ParticleSpawnLocation"));
	if (ParticleSpawnLocation)
		ParticleSpawnLocation->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> NSRef(TEXT("/Game/Particle/NigaraSystem/NS_Glitter.NS_Glitter"));
	if (NSRef.Succeeded())
		GlitterParticle = NSRef.Object;

	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxTrigger->SetCollisionObjectType(ECC_WorldStatic);
	BoxTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ACDBaseItem::DudeClear()
{
	if (NiagaraComp)
	{
		NiagaraComp->DestroyComponent();
	}
	
	Destroy();
}

// Called when the game starts or when spawned
void ACDBaseItem::BeginPlay()
{
	Super::BeginPlay();

	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GlitterParticle, ParticleSpawnLocation->GetComponentLocation());

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACDBaseItem::BeginOverlapBoxTrigger);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ACDBaseItem::EndOverlapBoxTrigger);
}

// Called every frame
void ACDBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACDBaseItem::BeginOverlapBoxTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInterface_Pickme* Pickme = Cast<IInterface_Pickme>(OtherActor))
	{
		Pickme->Pickme(Coment, this);
	}
}

void ACDBaseItem::EndOverlapBoxTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInterface_Pickme* Pickme = Cast<IInterface_Pickme>(OtherActor))
	{
		Pickme->Pickme(TEXT(""), nullptr);
	}
}

