// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

    // Устанавливаем дефолтные значения
    bIsOpening = false;
	bMove = false;
    DoorSpeed = 2.0f;
    OpenAngle = 90.0f;

}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = DoorMesh->GetRelativeRotation();
	TargetRotation = InitialRotation;
	
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation;

	if(bMove)
	{
		CurrentRotation = DoorMesh->GetRelativeRotation();
    	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, DoorSpeed);
    	DoorMesh->SetRelativeRotation(NewRotation);
	}

	
}

void ADoorActor::Interact_Implementation(AActor *Caller)
{
	if (!bIsOpening)
	{
  	  	bIsOpening = true;
      	TargetRotation = InitialRotation + FRotator(0.f, OpenAngle, 0.f); // поворот на 90 градусов
	}
	else
	{
		bIsOpening = false; 
		TargetRotation = InitialRotation;

	}

	bMove = true;

}




