// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KoEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KINGDOMOFENOCH_API AKoEPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    virtual void SetupInputComponent() override;

    // Example interaction request from client server
    UFUNCTION(Server, Reliable)
    void ServerTryInteract();
};
