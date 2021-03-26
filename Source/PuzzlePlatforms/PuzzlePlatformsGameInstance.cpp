// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

#include "PuzzlePlatformsGameInstance.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer) 
{
    UE_LOG(LogTemp, Warning, TEXT("This is constructor"));
}

void UPuzzlePlatformsGameInstance::Init() 
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("This is Init Function"));
}

void UPuzzlePlatformsGameInstance::Host() 
{
    UEngine* Engine = GetEngine();
    
    if(Engine == nullptr) return;
    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

    UWorld* World = GetWorld();
    if(World == nullptr) return;

    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(FString& IpAddress) 
{
    UEngine* Engine = GetEngine();
    
    if(Engine == nullptr) return;
    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *IpAddress));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if(PlayerController == nullptr) return;

    PlayerController->ClientTravel(*IpAddress, ETravelType::TRAVEL_Absolute);
}
