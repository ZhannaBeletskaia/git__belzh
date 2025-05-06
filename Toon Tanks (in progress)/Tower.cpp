// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay(); // compilation error 

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(inFireRange())
        RotateTurret(tank->GetActorLocation());

    
}

void ATower::CheckFireCondition()
{
    if(inFireRange())
        Fire();
}

bool ATower::inFireRange()
{
    if(tank)
    {
        float dist = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
        if(dist <= FireRange)
        {
            return true;
        }
    }
    
    return false;
}
