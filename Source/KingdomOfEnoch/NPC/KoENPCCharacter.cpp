// Fill out your copyright notice in the Description page of Project Settings.


#include "KoENPCCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "KoEAIController.h"
#include "../Components/KoEInteractableComponent.h"
#include "../Components/KoEQuestGiverComponent.h"
#include "../Components/KoEVendorComponent.h"

AKoENPCCharacter::AKoENPCCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKoEAIController::StaticClass();

    Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
    Interactable = CreateDefaultSubobject<UKoEInteractableComponent>(TEXT("Interactable"));
    QuestGiver = CreateDefaultSubobject<UKoEQuestGiverComponent>(TEXT("QuestGiver"));
    Vendor = CreateDefaultSubobject<UKoEVendorComponent>(TEXT("Vendor"));
}

void AKoENPCCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (Interactable)
    {
        Interactable->OnInteracted.AddDynamic(this, &AKoENPCCharacter::HandleInteracted);
    }
}

void AKoENPCCharacter::HandleInteracted(APawn* InstigatorPawn)
{
    if (QuestGiver)
    {
        QuestGiver->GiveQuestsTo(InstigatorPawn);
    }
    if (Vendor)
    {
        if (APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController()))
        {
            Vendor->OpenShopUI(PC);
        }
    }
}
