// Fill out your copyright notice in the Description page of Project Settings.


#include "LightActor.h"
#include "Components/PointLightComponent.h"

// Sets default values
ALightActor::ALightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    RootComponent = PointLight;

	Bulb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bulb"));
	Bulb->SetupAttachment(RootComponent);

	BulbBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulbBase"));
	BulbBase->SetupAttachment(Bulb);

}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility(false);
	
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightActor::TurnOnLight()
{
	float R = FMath::FRand(); 
    float G = FMath::FRand();
    float B = FMath::FRand();

    PointLight->SetLightColor(FLinearColor(R, G, B));
	PointLight->SetVisibility(true);
}

void ALightActor::TurnOffLight()
{
	PointLight->SetVisibility(false);
}
