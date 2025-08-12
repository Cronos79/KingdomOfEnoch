// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KoEHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOMOFENOCH_API UKoEHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKoEHealthComponent();





protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
    void ApplyDamage(float Amount);

protected:
    UFUNCTION()
    void OnRep_Health(float OldHealth);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& Out) const override;

public:
	UPROPERTY(BlueprintAssignable) 
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Health, EditDefaultsOnly, Category="Health")
    float Health = 100.f;
		
};
