// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Pawn's components")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Pawn's components")
	class UCameraComponent * camera;

	UPROPERTY(EditAnywhere, Category = "Pawn's components")
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Pawn's components")
	float TurnRate = 50.f;

	APlayerController* PlayerControllerRef;

	void Move(float Value);
	void Turn(float value);
};
