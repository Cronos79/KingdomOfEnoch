// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KoEVendorComponent.generated.h"

USTRUCT(BlueprintType)
struct FKoEShopItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UObject> Item; // swap to your item class later
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Price = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOMOFENOCH_API UKoEVendorComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Shop")
    TArray<FKoEShopItem> Inventory;

    UFUNCTION(BlueprintCallable, Category="Shop")
    void OpenShopUI(APlayerController* PC);	
};
