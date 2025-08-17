// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KoECharacterBase.generated.h"

class UKoEHealthComponent; // your existing health component

UCLASS()
class KINGDOMOFENOCH_API AKoECharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
    AKoECharacterBase();

    UFUNCTION(BlueprintPure, Category="KOE|Components")
    FORCEINLINE UKoEHealthComponent* GetHealthComponent() const { return HealthComp; }

    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="KOE|Character")
    void OnHealthChanged(float OldHealth, float NewHealth);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="KOE|Components")
    TObjectPtr<UKoEHealthComponent> HealthComp;
};
