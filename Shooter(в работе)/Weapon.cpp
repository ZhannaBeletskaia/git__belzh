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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShootingFrom;
	
	bool bSuccess = GunTrace(HitResult, ShootingFrom);
	
	if(bSuccess)
		{
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShootingFrom.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);

			AActor* HitActor = HitResult.GetActor();

			if(HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, HitResult, ShootingFrom, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
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

bool AWeapon::GunTrace(FHitResult &HitResult, FVector &ShootingFrom)
{
	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false;

	FVector location;
	FRotator rotation;

	OwnerController->GetPlayerViewPoint(location, rotation);
	ShootingFrom = -rotation.Vector(); // направление от точки попадания к игроку, не самый точный способ

	FVector End = location + rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController *AWeapon::GetOwnerController() const
{
  	// получим owner оружия, чтоб получить его controller
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if(!GunOwner) return nullptr;

	return GunOwner->GetController();
}
