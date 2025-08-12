// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Components/KoEHealthComponent.h"
#include "KoECharacter.generated.h"

UCLASS()
class KINGDOMOFENOCH_API AKoECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKoECharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UCameraComponent* TopDownCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UKoEHealthComponent* HealthComp;
};
