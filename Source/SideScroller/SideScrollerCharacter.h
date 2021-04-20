// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "SideScrollerCharacter.generated.h"

UCLASS(config=Game)
class ASideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;

protected:


	//void OnGrab();

	/** Called for side to side input */
	void MoveRight(float Val);
	/** Called for forwards and backwards input */
	void MoveForward(float Value);

	

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



public:
	ASideScrollerCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool AllowMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool MoveForwards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool IsPushing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool InMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector camForwardVector = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector camRightVector = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool PlayPushAudio; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* pushSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAudioComponent* PushAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float PushingAnimValue;
protected:
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
};
