// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "KoEPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class KINGDOMOFENOCH_API AKoEPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AKoEPlayerController();

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

protected:
    UFUNCTION()
    void Input_Move2D(const FInputActionValue& V);
    UFUNCTION()
    void Input_Interact();

    UFUNCTION(Server, Reliable)
    void ServerTryInteract();

protected:
    UPROPERTY() UInputMappingContext* IMC_Default = nullptr;
    UPROPERTY() UInputAction* IA_Move = nullptr;
    UPROPERTY() UInputAction* IA_Interact    = nullptr;
};
