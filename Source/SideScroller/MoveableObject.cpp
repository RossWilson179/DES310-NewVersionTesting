// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"
#include "Engine/Engine.h"


AMoveableObject::AMoveableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//InteractableMesh->SetMaterial(0,MoveableMaterial);
	InteractableMeshComponent->SetVisibility(true);
	InteractableMeshComponent->SetSimulatePhysics(true);
	InteractableMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OnActorBeginOverlap.AddDynamic(this, &AMoveableObject::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMoveableObject::OnOverlapEnd);


}
void AMoveableObject::Interact_Implementation()
{


}
void AMoveableObject::OnOverlapBegin(class AActor* OverlappingActor, class AActor* OtherActor)
{
	/*if (OtherActor && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Overlapping Start");

	}*/



}

void AMoveableObject::OnOverlapEnd(class AActor* OverlappingActor, class AActor* OtherActor)
{
	/*if (OtherActor && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Overlapping End");

	}*/

}
