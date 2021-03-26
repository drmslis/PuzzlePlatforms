// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "PlatformTrigger.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	
	if(TriggerVolume != nullptr)
	{
		RootComponent = TriggerVolume;
	}

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	for(AMovingPlatform* CurrentPlatform : PlatformsTrigger)
	{
		if(CurrentPlatform != nullptr) CurrentPlatform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	for(AMovingPlatform* CurrentPlatform : PlatformsTrigger)
	{
		if(CurrentPlatform != nullptr) CurrentPlatform->RemoveActiveTrigger();
	}
}




// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

