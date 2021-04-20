// Fill out your copyright notice in the Description page of Project Settings.

#include "KidAIController.h"
#include "KidCharacter.h"
#include "KidWaypoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SideScrollerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AKidAIController::AKidAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AKidAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AKidAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("All Systems Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Some Problem Occured"));
	}
}

void AKidAIController::OnPossess(APawn * PawnTemp)
{
	Super::OnPossess(PawnTemp);
	UE_LOG(LogTemp, Warning, TEXT("Possessed"));
}

void AKidAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AKidCharacter* KidCharacterTemp = Cast<AKidCharacter>(GetPawn());

	if (DistanceToPlayer > AISightRadius)
	{
		bIsPlayerDetected = false;
	}
	
	ASideScrollerCharacter* Player = Cast<ASideScrollerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	DistanceToPlayer = GetPawn()->GetDistanceTo(Player);

	WaypointType WPType = KidCharacterTemp->CurrentKidWaypoint->Type;

	switch (WPType)
	{
	case MidPoint:
		//Move to KidWaypoint
		if (KidCharacterTemp->NextKidWaypoint != nullptr && bIsPlayerDetected == true)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Midpoint move"));
			MoveToActor(KidCharacterTemp->NextKidWaypoint, 5.0f);
		}
		else
		{
			//if (bIsPlayerDetected) UE_LOG(LogTemp, Warning, TEXT("Midpoint else stop: player is not detected"))
			//else UE_LOG(LogTemp, Warning, TEXT("Midpoint else stop: next waypoint is nullptr"));
			StopMovement();
		}
		break;
	case Teleport:
		StopMovement();

		//if teleport location not already specified, set the location that they'll be teleporting to to the position of the next waypoint
		if (KidCharacterTemp->CurrentKidWaypoint->TPX == 0 && KidCharacterTemp->CurrentKidWaypoint->TPY == 0 && KidCharacterTemp->CurrentKidWaypoint->TPZ == 0)
		{
			KidCharacterTemp->CurrentKidWaypoint->TPX = KidCharacterTemp->NextKidWaypoint->GetActorLocation().X;
			KidCharacterTemp->CurrentKidWaypoint->TPY = KidCharacterTemp->NextKidWaypoint->GetActorLocation().Y;
			KidCharacterTemp->CurrentKidWaypoint->TPZ = KidCharacterTemp->NextKidWaypoint->GetActorLocation().Z;
		}

		//teleport
		KidCharacterTemp->SetActorLocation(FVector(KidCharacterTemp->CurrentKidWaypoint->TPX, KidCharacterTemp->CurrentKidWaypoint->TPY, KidCharacterTemp->CurrentKidWaypoint->TPZ));
		UE_LOG(LogTemp, Warning, TEXT("Teleported"));
		break;
	default:
		break;
	}
	
}

FRotator AKidAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Pawn is nullptr"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Pawn is not nullptr"));
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AKidAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for (size_t i = 0; i < DetectedPawns.Num(); i++)
	{
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);

		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);
	}

	bIsPlayerDetected = true;
}
