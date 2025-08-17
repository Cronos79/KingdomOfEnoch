// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEHUD.h"
#include "KoEMainHUDWidget.h"
#include "../Core/KoEPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "../Quests/QuestLogComponent.h"

void AKoEHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MainHUDClass)
    {
        MainHUD = CreateWidget<UKoEMainHUDWidget>(GetWorld(), MainHUDClass);
        if (MainHUD)
        {
            MainHUD->AddToViewport();
        }
    }

    APlayerController* PC = PlayerOwner; // HUD has PlayerOwner on clients
    if (PC)
    {
        if (AKoEPlayerState* PS = PC->GetPlayerState<AKoEPlayerState>())
        {
            QuestLogRef = PS->FindComponentByClass<UQuestLogComponent>();
            if (QuestLogRef)
            {
                QuestLogRef->OnQuestUpdated.AddDynamic(this, &AKoEHUD::HandleQuestUpdated);
                QuestLogRef->OnObjectiveUpdated.AddDynamic(this, &AKoEHUD::HandleObjectiveUpdated);

                if (MainHUD)
                {
                    MainHUD->RefreshFromQuestLog(QuestLogRef);
                }
            }
        }
    }
}

void AKoEHUD::HandleQuestUpdated(const FQuestRuntime& Quest)
{
    if (MainHUD && QuestLogRef)
    {
        MainHUD->RefreshFromQuestLog(QuestLogRef);
    }
}

void AKoEHUD::HandleObjectiveUpdated(FPrimaryAssetId QuestId, FName ObjectiveId, const FObjectiveRuntime& Runtime)
{
    if (MainHUD)
    {
        MainHUD->OnQuestObjectiveUpdated(QuestId, ObjectiveId, Runtime);
    }
}