// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingDoorComponent.h"

// Sets default values for this component's properties
UMovingDoorComponent::UMovingDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovingDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMovingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Target = OriginalLocation;
	if(ShouldMove)
	{
		Target = OriginalLocation + MoverOffset;
	}
	
	FVector Current = GetOwner()->GetActorLocation();
	
	float Speed = MoverOffset.Length() / MoveTime;

	FVector New_location = FMath::VInterpConstantTo(Current, Target, DeltaTime, Speed);

	GetOwner()->SetActorLocation(New_location);
}

void UMovingDoorComponent::SetShouldMove(bool should)
{
	ShouldMove = should;
}
