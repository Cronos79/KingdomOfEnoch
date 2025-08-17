// Fill out your copyright notice in the Description page of Project Settings.
#include "KoEQuestGiverComponent.h"
#include "../Quests/QuestLogComponent.h"
#include "GameFramework/PlayerState.h"

void UKoEQuestGiverComponent::GiveQuestsTo(APawn* Pawn)
{
    if (!Pawn) return;
    if (APlayerState* PS = Pawn->GetPlayerState())
    {
        if (UQuestLogComponent* Log = PS->FindComponentByClass<UQuestLogComponent>())
        {
            for (UQuestDataAsset* Q : QuestsToStart)
            {
                if (Q) Log->StartQuest(Q);
            }
        }
    }
}