// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/KoECharacterBase.h"
#include "KoENPCCharacter.generated.h"

class UAIPerceptionComponent;

class UKoEInteractableComponent;
class UKoEQuestGiverComponent;
class UKoEVendorComponent;

UCLASS()
class KINGDOMOFENOCH_API AKoENPCCharacter : public AKoECharacterBase
{
	GENERATED_BODY()
public:
    AKoENPCCharacter();

protected:
    void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="KOE|AI")
    TObjectPtr<UAIPerceptionComponent> Perception;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="KOE|Interact")
    TObjectPtr<UKoEInteractableComponent> Interactable;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="KOE|NPC")
    TObjectPtr<UKoEQuestGiverComponent> QuestGiver;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="KOE|NPC")
    TObjectPtr<UKoEVendorComponent> Vendor;
    UFUNCTION()
    void HandleInteracted(APawn* InstigatorPawn);
};
