// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(mover == nullptr)
        return;

    AActor* actor = GetAcceptableActor();

    if(actor != nullptr)
    {
        UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
        if(component != nullptr)
            component->SetSimulatePhysics(false);

        actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        mover->SetShouldMove(true);
    }
    else
        mover->SetShouldMove(false);
        
}

void UTriggerComponent:: SetMover(UMovingDoorComponent* newmover)
{
    mover = newmover;
}

AActor* UTriggerComponent:: GetAcceptableActor() const
{
    TArray<AActor*> Actors;

    GetOverlappingActors(Actors);
        
    for(AActor* actor : Actors)
    {
        if(actor->ActorHasTag(AcceptableActorTag) && !actor->ActorHasTag("Grabbed"))
            return actor;
    }

    return nullptr;
}
