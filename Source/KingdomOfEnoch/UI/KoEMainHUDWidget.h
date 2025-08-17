// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Quests/QuestTypes.h"
#include "KoEMainHUDWidget.generated.h"

class UQuestLogComponent;

UCLASS()
class KINGDOMOFENOCH_API UKoEMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    // Implement these in your WBP_MainHUD Blueprint
    UFUNCTION(BlueprintImplementableEvent, Category="Quests")
    void RefreshFromQuestLog(UQuestLogComponent* Log);

    UFUNCTION(BlueprintImplementableEvent, Category="Quests")
    void OnQuestObjectiveUpdated(FPrimaryAssetId QuestId, FName ObjectiveId, const FObjectiveRuntime& Runtime);	
};
