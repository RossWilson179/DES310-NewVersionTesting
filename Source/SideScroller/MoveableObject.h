// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MoveableObject.generated.h"

/**
 *
 */
UCLASS()
class SIDESCROLLER_API AMoveableObject : public AInteractableObject
{
	GENERATED_BODY()
public:
	AMoveableObject();
	virtual void Interact_Implementation() override;
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappingActor, class AActor* OtherActor);
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappingActor, class AActor* OtherActor);
	//	UPROPERTY(EditAnywhere)
		//	UMaterial* MoveableMaterial;

	//	UBoxComponent* CollisionMesh = nullptr;
};