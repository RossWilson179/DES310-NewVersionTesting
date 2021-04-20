// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "KidWaypoint.generated.h"



UENUM()
enum WaypointType
{
	MidPoint     UMETA(DisplayName = "MidPoint"),
	Teleport   UMETA(DisplayName = "Teleport"),
};

UCLASS()
class SIDESCROLLER_API AKidWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKidWaypoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AKidWaypoint* NextKidWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<WaypointType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TPX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TPY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TPZ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerEnter(UPrimitiveComponent* OverlapComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

};
