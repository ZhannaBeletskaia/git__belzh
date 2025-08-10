// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightActor.generated.h"

UCLASS(Blueprintable)
class TAGANROG_API ALightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* PointLight; // проинициализировать

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Bulb;

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BulbBase;

public:

	UFUNCTION(BlueprintCallable)
	void TurnOnLight();

	UFUNCTION(BlueprintCallable)
	void TurnOffLight();

};
