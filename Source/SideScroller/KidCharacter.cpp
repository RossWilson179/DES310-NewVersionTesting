// Fill out your copyright notice in the Description page of Project Settings.


#include "KidCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AKidCharacter::AKidCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("Character is set"));

}

// Called when the game starts or when spawned
void AKidCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKidCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
