// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEHealthComponent.h"
#include "Net/UnrealNetwork.h"

UKoEHealthComponent::UKoEHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UKoEHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKoEHealthComponent::ApplyDamage(float Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		float Old = Health;
		Health = FMath::Max(0.f, Health - Amount);
		OnHealthChanged.Broadcast(Health, Health - Old);
	}
}

void UKoEHealthComponent::OnRep_Health(float OldHealth)
{
	OnHealthChanged.Broadcast(Health, Health - OldHealth);
}

void UKoEHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UKoEHealthComponent, Health, COND_None, REPNOTIFY_Always);
}

