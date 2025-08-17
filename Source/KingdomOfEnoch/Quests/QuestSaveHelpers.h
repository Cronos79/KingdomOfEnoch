// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "QuestLogComponent.h"
#include "QuestSaveGame.h"
#include "QuestSaveHelpers.generated.h"

UCLASS()
class KINGDOMOFENOCH_API UQuestSaveHelpers : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Quests")
    static bool SaveQuests(UObject* WorldContextObject, UQuestLogComponent* Log, const FString& SlotName = TEXT("Quests"), int32 UserIndex = 0)
    {
        if (!WorldContextObject || !Log) return false;
        UQuestSaveGame* SaveObj = Cast<UQuestSaveGame>(UGameplayStatics::CreateSaveGameObject(UQuestSaveGame::StaticClass()));
        if (!SaveObj) return false;
        SaveObj->Quests.Reset();
        for (const FQuestRuntime& R : Log->GetAllQuests())
        {
            FQuestSaveEntry E; E.Runtime = R; SaveObj->Quests.Add(E);
        }
        return UGameplayStatics::SaveGameToSlot(SaveObj, SlotName, UserIndex);
    }

    UFUNCTION(BlueprintCallable, Category="Quests")
    static bool LoadQuests(UObject* WorldContextObject, UQuestLogComponent* Log, const FString& SlotName = TEXT("Quests"), int32 UserIndex = 0)
    {
        if (!WorldContextObject || !Log) return false;
        if (UQuestSaveGame* SaveObj = Cast<UQuestSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
        {
            // NOTE: Minimal restore — assumes assets are already known/loaded elsewhere.
            for (const FQuestSaveEntry& E : SaveObj->Quests)
            {
                // If already present, skip; else add
                if (!Log->GetAllQuests().ContainsByPredicate([&](const FQuestRuntime& R){ return R.QuestAssetId == E.Runtime.QuestAssetId; }))
                {
                    Log->GetAllQuests().Add(E.Runtime); // For simplicity; you may want a setter.
                }
            }
            return true;
        }
        return false;
    }
};