// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestTypes.h"
#include "QuestLogComponent.h"
#include "QuestFunctionLib.generated.h"

UCLASS()
class UQuestFunctionLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // Broadcast a quest progress event from anywhere (e.g., pickups, triggers, NPC dialogues)
    UFUNCTION(BlueprintCallable, Category="Quests")
    static bool FireQuestEventByTag(AActor* ActorWithQuestLog, FGameplayTag EventTag, int32 Amount = 1)
    {
        if (!ActorWithQuestLog) return false;
        if (UQuestLogComponent* Log = ActorWithQuestLog->FindComponentByClass<UQuestLogComponent>())
        {
            return Log->AddObjectiveProgressByTag(EventTag, Amount);
        }
        return false;
    }
};
