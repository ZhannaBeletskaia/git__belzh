// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS(Blueprintable)
class TAGANROG_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	public:
    // Root
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* Root;

    // Основа лифта (направляющая)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Base;

    // Подвижная платформа
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Platform;

    // Constraint между Base и Platform
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UPhysicsConstraintComponent* PhysicsConstraint;

public:
    // Движение (включение мотора)
    void StartElevator();

private:

    FVector InitHeight;
    FVector Target;
    bool goDown;

};
