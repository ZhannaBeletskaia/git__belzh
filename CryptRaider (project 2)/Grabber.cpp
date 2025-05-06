// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(physicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("physics handle name %s"), *physicsHandle->GetName());
	}
	else
		UE_LOG(LogTemp, Display, TEXT("physics handle is nullptr"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * HoldDist;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
		
	
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if(physicsHandle && physicsHandle->GetGrabbedComponent())
		{
			physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
			physicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
			physicsHandle->ReleaseComponent();
			
		}
	else
		return;
}

bool UGrabber::GetGrabbableInReach(FHitResult &HitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	//DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5);

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(HitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);
}

void UGrabber::Grab()
{
	FHitResult HitResult;

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(physicsHandle == nullptr)
		return;
	
	if(GetGrabbableInReach(HitResult))
	{
		HitResult.GetComponent()->SetSimulatePhysics(true); 
		HitResult.GetComponent()->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");

		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		physicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	

	//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
	//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Yellow, false, 5);
}

