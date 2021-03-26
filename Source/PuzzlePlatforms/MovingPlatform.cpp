// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

void AMovingPlatform::BeginPlay() 
{
    Super::BeginPlay();

    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
    
    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::AddActiveTrigger() 
{
    CurrentTriggers++;
    if(CurrentTriggers >= ActiveTriggers) bIsPlatformActive = true;    
}

void AMovingPlatform::RemoveActiveTrigger() 
{
    if(CurrentTriggers > 0) CurrentTriggers--;
    if(CurrentTriggers < ActiveTriggers) bIsPlatformActive = false;
}

bool AMovingPlatform::IsActive() 
{
    return bIsPlatformActive;
}

AMovingPlatform::AMovingPlatform() 
{
    PrimaryActorTick.bCanEverTick = true;   
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    
    if (!bIsPlatformActive) return;

    if (HasAuthority())
    {   
        //AddActorLocalOffset(MovingDirection.GetSafeNormal() * Speed * DeltaSeconds);       
        FVector Location = GetActorLocation();
        float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
        float JourneyTraveled = (Location - GlobalStartLocation).Size();

        if(JourneyTraveled >= JourneyLength)
        {
            FVector Swap = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = Swap;
        }

        FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
        FVector MovingDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

        Location += Speed * DeltaSeconds * MovingDirection.GetSafeNormal();
        SetActorLocation(Location);
    }    
}


