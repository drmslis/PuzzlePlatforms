// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Math/Vector.h"
#include "MovingPlatform.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

	UFUNCTION(BlueprintPure)
	bool IsActive();

private:
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;	

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;
	int32 CurrentTriggers = 0;

	UPROPERTY()
	bool bIsPlatformActive = false;


};
