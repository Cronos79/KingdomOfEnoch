// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/KoECharacterBase.h"
#include "KoEPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class KINGDOMOFENOCH_API AKoEPlayerCharacter : public AKoECharacterBase
{
    GENERATED_BODY()
public:
    AKoEPlayerCharacter();

    UPROPERTY(EditAnywhere, Category = "Interact")
    float InteractDistance = 250.f;
    UPROPERTY(EditAnywhere, Category = "Interact")
    float InteractRadius = 32.f;
    UFUNCTION(BlueprintCallable)
    void TryInteract();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KOE|Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KOE|Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> TopDownCamera;
};
