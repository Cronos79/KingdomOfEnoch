// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestTypes.h"
#include "QuestSaveGame.generated.h"

USTRUCT()
struct FQuestSaveEntry
{
    GENERATED_BODY()

    UPROPERTY()
    FQuestRuntime Runtime;
};

UCLASS()
class KINGDOMOFENOCH_API UQuestSaveGame : public USaveGame
{
	GENERATED_BODY()
	public:
    UPROPERTY()
    TArray<FQuestSaveEntry> Quests;	
};