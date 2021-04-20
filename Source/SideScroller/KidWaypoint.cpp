// Fill out your copyright notice in the Description page of Project Settings.


#include "KidWaypoint.h"
#include "KidCharacter.h"

// Sets default values
AKidWaypoint::AKidWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKidWaypoint::OnPlayerEnter);
}

// Called when the game starts or when spawned
void AKidWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKidWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKidWaypoint::OnPlayerEnter(UPrimitiveComponent * OverlapComponent,
	AActor * OtherActor,
	UPrimitiveComponent * OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult)
{
	AKidCharacter* Character = nullptr;
	if (OtherActor != nullptr)
	{
		Character = Cast<AKidCharacter>(OtherActor);
		if (Character != nullptr)
		{
			Character->NextKidWaypoint = NextKidWaypoint;
			Character->CurrentKidWaypoint = this;
		}
	}
}

