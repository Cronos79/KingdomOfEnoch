// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KoEGameState.generated.h"

/**
 * 
 */
UCLASS()
class KINGDOMOFENOCH_API AKoEGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
    AKoEGameState();

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category="Game")
    int32 WorldDay = 1;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const override;
};
