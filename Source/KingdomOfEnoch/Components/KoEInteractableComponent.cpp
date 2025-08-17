// Fill out your copyright notice in the Description page of Project Settings.
#include "KoEInteractableComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UKoEInteractableComponent::UKoEInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKoEInteractableComponent::Interact_Implementation(APawn* InstigatorPawn)
{
	OnInteracted.Broadcast(InstigatorPawn);
}