// Fill out your copyright notice in the Description page of Project Settings.
#include "KoEVendorComponent.h"
#include "GameFramework/PlayerController.h"

void UKoEVendorComponent::OpenShopUI(APlayerController* PC)
{
    // TODO: Replace with your WBP_Shop spawning. This is just a placeholder log.
    UE_LOG(LogTemp, Log, TEXT("OpenShopUI: Inventory has %d items"), Inventory.Num());
}