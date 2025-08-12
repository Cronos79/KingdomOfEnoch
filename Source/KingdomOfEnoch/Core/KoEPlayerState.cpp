// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEPlayerState.h"
#include "Net/UnrealNetwork.h"

AKoEPlayerState::AKoEPlayerState()
{
	bReplicates = true;
}

void AKoEPlayerState::OnRep_Level()
{

}

void AKoEPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKoEPlayerState, Level);
}
