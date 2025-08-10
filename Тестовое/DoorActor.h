// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "DoorActor.generated.h"

UCLASS()
class TAGANROG_API ADoorActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact_Implementation(AActor* Caller) override;

private:

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

	// Состояние двери (открыта/закрыта)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
    bool bIsOpening;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
    bool bMove;

    // Скорость открытия/закрытия
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
    float DoorSpeed;

    // Угол открытия (в градусах)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
    float OpenAngle;

    // Начальный поворот двери
    FRotator InitialRotation;
	FRotator TargetRotation;

};
