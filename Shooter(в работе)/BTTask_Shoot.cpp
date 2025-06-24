// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "MyShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
        return EBTNodeResult::Failed;

    AMyShooterCharacter* Enemy = Cast<AMyShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if(Enemy == nullptr)
        return EBTNodeResult::Failed;

    Enemy->GetTriggerPulled();

    return EBTNodeResult::Succeeded;


}