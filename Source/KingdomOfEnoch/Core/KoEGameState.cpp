// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEGameState.h"
#include "Net/UnrealNetwork.h"

AKoEGameState::AKoEGameState()
{
	bReplicates = true;
}

void AKoEGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AKoEGameState, WorldDay);
}
