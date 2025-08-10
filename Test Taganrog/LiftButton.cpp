// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftButton.h"
#include "Elevator.h"
#include "Components/BoxComponent.h"

// Sets default values
ALiftButton::ALiftButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    RootComponent = ButtonMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);

}

void ALiftButton::Interact_Implementation(AActor *Caller)
{
	elevator->StartElevator();
}

// Called when the game starts or when spawned
void ALiftButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALiftButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

