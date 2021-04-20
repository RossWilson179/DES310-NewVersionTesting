// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SideScrollerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"

ASideScrollerCharacter::ASideScrollerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	PushAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Push Audio Component"));
	PushAudioComponent->SetupAttachment(RootComponent);
	PushAudioComponent->bAutoActivate = false;


	//static ConstructorHelpers::FObjectFinder<USoundBase> MySoundFile(TEXT("Audio/dog_push_grunt"));
//u	pushSound = MySoundFile.Object;

	MoveForwards = false;
	IsPushing = false;
	AllowMovement = true;
	InMenu = false;
	PlayPushAudio = true;
	//JumpAudio = false;
	PushingAnimValue = 0;

	
}


void ASideScrollerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//OnActorBeginOverlap.AddDynamic(this, &ASideScrollerCharacter::OnOverlapBegin);
	//OnActorEndOverlap.AddDynamic(this, &ASideScrollerCharacter::OnOverlapEnd);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASideScrollerCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ASideScrollerCharacter::OnOverlapEnd);
	PushAudioComponent->SetSound(pushSound);

	//PushAudioComponent->SetActive(true);
	//PushAudioComponent->Play();

}

void ASideScrollerCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	camForwardVector = CameraBoom->GetForwardVector();
	camRightVector = CameraBoom->GetRightVector();

}

//////////////////////////////////////////////////////////////////////////
// Input

void ASideScrollerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &ASideScrollerCharacter::OnGrab);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASideScrollerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASideScrollerCharacter::MoveForward);

}

void ASideScrollerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void ASideScrollerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

 

/*void ASideScrollerCharacter::OnGrab()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Grab button pressed"));
}*/

void ASideScrollerCharacter::MoveRight(float Value)
{
	// add movement in that direction
	if (AllowMovement)
	{
		/*const FRotator Rotation = Controller->GetControlRotation();
			const FRotator Yaw(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);*/

		//AddMovementInput(FVector(0.0f, -1.0f, 0.0f), Value);
		if (MoveForwards == false)
		{
			AddMovementInput(FVector(0.0f, -1.0f, 0.0f), Value);
		}

		else
		{
			AddMovementInput(camRightVector, Value);
		}
	}
	
	if (IsPushing)
	{
		PushingAnimValue = Value;
		if (PushAudioComponent != NULL && PushAudioComponent->IsPlaying() == false)
		{
			
			//UGameplayStatics::PlaySoundAtLocation(this, pushSound, GetActorLocation());
			//PlayPushAudio = false;
			PushAudioComponent->Activate(true);
			PushAudioComponent->Play();
			//UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, pushSound);
			//AudioComponent->SetActive(false);
		}
	}

	//if (!IsPushing)
	//{
	//	PlayPushAudio = true;
	//}
	if (!IsPushing && PushAudioComponent->IsPlaying())
	{
		PushAudioComponent->Stop();
	}

}
void ASideScrollerCharacter::MoveForward(float Value)
{
	if (MoveForwards && AllowMovement)
	{
		/*const FRotator Rotation = Controller->GetControlRotation();
			const FRotator Yaw(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);*/
			//AddMovementInput(FVector(-1.0, 0.0f, 0.0f), Value);
		AddMovementInput(camForwardVector, Value);

		if (IsPushing)
		{
			//PushingAnimValue = Value;

			if (PushAudioComponent != NULL && PushAudioComponent->IsPlaying() == false)
			{
				PushAudioComponent->Play();
				//UGameplayStatics::PlaySoundAtLocation(this, pushSound, GetActorLocation());
				//PlayPushAudio = false;
				
			}
		}
		//if (!IsPushing)
		//{
		//	PlayPushAudio = true;
		//}
		if (!IsPushing && PushAudioComponent->IsPlaying())
		{
			PushAudioComponent->Stop();
		}



	}
}




