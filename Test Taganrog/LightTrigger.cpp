// Fill out your copyright notice in the Description page of Project Settings.


#include "LightTrigger.h"
#include "Components/BoxComponent.h"
#include "LightActor.h"

// Sets default values
ALightTrigger::ALightTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerBox->SetGenerateOverlapEvents(true);

    

}

// Called when the game starts or when spawned
void ALightTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALightTrigger::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALightTrigger::OnOverlapEnd);

	UE_LOG(LogTemp, Warning, TEXT("delegates are set"));
	
}

// Called every frame
void ALightTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                   bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("overlap begin"));

    if (LinkedLight)
    {
        LinkedLight->TurnOnLight();
    }
	else
		UE_LOG(LogTemp, Warning, TEXT("no light class initialized"));
}

void ALightTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (LinkedLight)
    {
        LinkedLight->TurnOffLight();
    }
}
