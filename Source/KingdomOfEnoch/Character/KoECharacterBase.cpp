#include "KoECharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/KoEHealthComponent.h"

AKoECharacterBase::AKoECharacterBase()
{
    PrimaryActorTick.bCanEverTick = false;

    // Move your existing HealthComponent creation here
    HealthComp = CreateDefaultSubobject<UKoEHealthComponent>(TEXT("HealthComp"));
}

void AKoECharacterBase::BeginPlay()
{
    Super::BeginPlay();
    // If your HealthComponent exposes delegates, bind them here. Example:
    if (HealthComp) { HealthComp->OnHealthChanged.AddDynamic(this, &AKoECharacterBase::OnHealthChanged); }
}

