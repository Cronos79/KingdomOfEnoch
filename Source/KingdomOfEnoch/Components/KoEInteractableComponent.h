// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/KoEInteractable.h"
#include "KoEInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKoEOnInteracted, APawn*, InstigatorPawn);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOMOFENOCH_API UKoEInteractableComponent : public UActorComponent, public IKoEInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKoEInteractableComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact")
    FText Prompt = FText::FromString(TEXT("Interact"));

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact")
    bool bEnabled = true;

    // IKoEInteractable
    virtual bool CanInteract_Implementation(APawn* InstigatorPawn) const override { return bEnabled; }
    virtual void Interact_Implementation(APawn* InstigatorPawn) override;
    virtual FText GetInteractPrompt_Implementation() const override { return Prompt; }

    UPROPERTY(BlueprintAssignable, Category="Interact")
    FKoEOnInteracted OnInteracted;	
};
