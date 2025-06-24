// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// получим owner оружия, чтоб получить его controller
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if(GunOwner == nullptr) return;

	AController* OwnerController = GunOwner->GetController();
	if(OwnerController == nullptr) return;

	FVector location;
	FRotator rotation;

	OwnerController->GetPlayerViewPoint(location, rotation);

	FVector End = location + rotation.Vector() * MaxRange;

	FHitResult HitResult;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, location, End, ECollisionChannel::ECC_GameTraceChannel1);
	

	if(bSuccess)
		{
			FVector ShootingFrom = -rotation.Vector(); // направление от точки попадания к игроку, не самый точный способ
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShootingFrom.Rotation());

			AActor* HitActor = HitResult.GetActor();

			if(HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, HitResult, ShootingFrom, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}


	//                                         viewport, scale 
	//DrawDebugCamera(GetWorld(), location, rotation, 90, 2, FColor::Red, true); // так можно отрисовать положение камеры
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

