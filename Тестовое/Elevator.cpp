// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // Основа
    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    Base->SetupAttachment(Root);
    Base->SetSimulatePhysics(false); // неподвижная часть

    // Платформа
    Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
    Platform->SetupAttachment(Root);
	Platform->SetSimulatePhysics(false); // подвижная
   

    // Constraint
    PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
    PhysicsConstraint->SetupAttachment(Root);

    PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f); // чтоб не кренилось
    PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
    PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

}


// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	// Привязка constraint
    PhysicsConstraint->SetConstrainedComponents(Base, NAME_None, Platform, NAME_None);

    // Настройка ограничений движения
    PhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
    PhysicsConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
    PhysicsConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 800); // ограничение на расстрояние

    // Мотор по оси Z
    PhysicsConstraint->SetLinearVelocityDrive(false, false, true); // только Z
    PhysicsConstraint->SetLinearDriveParams(50000.f, 1000.f, 0.f); // сила

    InitHeight = Platform->GetComponentLocation();
    Target = InitHeight - FVector(0.f, 0.f, 800.f);
    goDown = true;
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentHeight = Platform->GetComponentLocation();
    if(CurrentHeight.Equals(Target, 1.0f))
    {
        goDown = !goDown;
        (!goDown) ? Target = InitHeight : Target = InitHeight - FVector(0.f, 0.f, 800.f);
        UE_LOG(LogTemp, Warning, TEXT("Сработала остановка в тике"));
        PhysicsConstraint->SetLinearVelocityTarget(FVector::ZeroVector);
    }
}

void AElevator::StartElevator()
{
    if (!Platform || !PhysicsConstraint)
	{
		UE_LOG(LogTemp, Error, TEXT("Platform or Constraint is nullptr!"));
		return;
	}

    float direction;
    if(goDown)
    {
        direction = 50.f; // скорость и направление
    }
    else
    {
        direction = -50.f; 
    }

    UE_LOG(LogTemp, Warning, TEXT("Platform: %s, Constraint: %s"),
       *GetNameSafe(Platform),
       *GetNameSafe(PhysicsConstraint));

	Platform->SetSimulatePhysics(true); // подвижная
	FVector TargetVelocity(0.f, 0.f, direction); // движение вниз
    
    PhysicsConstraint->SetLinearVelocityTarget(TargetVelocity);

}
