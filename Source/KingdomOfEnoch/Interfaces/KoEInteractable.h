// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KoEInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKoEInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KINGDOMOFENOCH_API IKoEInteractable
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interact")
    bool CanInteract(APawn* InstigatorPawn) const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interact")
    void Interact(APawn* InstigatorPawn);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interact")
    FText GetInteractPrompt() const;
	
	
};
