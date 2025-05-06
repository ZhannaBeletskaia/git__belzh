// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPLatform.h"

// Sets default values
AMovingPLatform::AMovingPLatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPLatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//FString name = GetName();

	//UE_LOG(LogTemp, Display, TEXT("Begin PLay Actor %s"), *name); 
	
}

// Called every frame
void AMovingPLatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
		
}

void AMovingPLatform::MovePlatform(float DeltaTime)
{
	if(GetDistanceMoved() > MaxDis)
	{
		FVector DirectionNormal = PlatformVelocity.GetSafeNormal();
		StartLocation += DirectionNormal * MaxDis;

		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPLatform::RotatePlatform(float DeltaTime)
{
	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRotation += RotationVelocity * DeltaTime;
	//SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

float AMovingPLatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

