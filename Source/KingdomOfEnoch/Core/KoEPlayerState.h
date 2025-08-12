// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KoEPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KINGDOMOFENOCH_API AKoEPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
    AKoEPlayerState();

protected:
    UPROPERTY(ReplicatedUsing=OnRep_Level, BlueprintReadOnly, Category="Player")
    int32 Level = 1;

    UFUNCTION()
    void OnRep_Level();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const override;
};
