// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTPathFollowingComponent.h"
#include "SoftDesignTraining.h"
#include "SDTUtils.h"
#include "SDTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "NavLinkCustomInterface.h"

#include "DrawDebugHelpers.h"

USDTPathFollowingComponent::USDTPathFollowingComponent(const FObjectInitializer& ObjectInitializer)
{

}

/**
* This function is called every frame while the AI is following a path.
* MoveSegmentStartIndex and MoveSegmentEndIndex specify where we are on the path point array.
*/
void USDTPathFollowingComponent::FollowPathSegment(float DeltaTime)
{
    const TArray<FNavPathPoint>& points = Path->GetPathPoints();
    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];
    const FNavPathPoint& segmentEnd = points[MoveSegmentEndIndex];

    AController* controller = Cast<AController>(GetOwner());
    APawn* pawn = controller->GetPawn();

    if (isJumping) //if (SDTUtils::HasJumpFlag(segmentStart))
    {
        // Update jump along path / nav link proxy
        jumProgress += DeltaTime;
        float time = FMath::Clamp(jumProgress, 0.f, 1.f);
        FVector location = FMath::Lerp(segmentStart.Location, segmentEnd.Location, time);
        location.Z += 300.f * 4.f * time * (1.f - time);
        pawn->SetActorLocation(location);
        if (time >= 1.f) isJumping = false;    
    }
    else
    {
        // Update navigation along path (move along)
        
        UNavMovementComponent* movement = Cast<UNavMovementComponent>(pawn->GetMovementComponent());
        FVector direction = segmentEnd.Location - pawn->GetActorLocation();;
        direction.Z = 0.0f;
        direction.Normalize();
        movement->RequestPathMove(direction);
    }
}

/**
* This function is called every time the AI has reached a new point on the path.
* If you need to do something at a given point in the path, this is the place.
*/
void USDTPathFollowingComponent::SetMoveSegment(int32 segmentStartIndex)
{
    Super::SetMoveSegment(segmentStartIndex);

    const TArray<FNavPathPoint>& points = Path->GetPathPoints();

    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];

    if (FNavMeshNodeFlags(segmentStart.Flags).IsNavLink()) //DTUtils::HasJumpFlag(segmentStart) && 
    {
        // Handle starting jump
        jumProgress = 0.f;
        isJumping = true;
    }
    else
    {
        // Handle normal segments
        isJumping = false;
    }
}

