// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestTypes.h"
#include "QuestDataAsset.generated.h"

UCLASS(BlueprintType)
class KINGDOMOFENOCH_API UQuestDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName QuestId = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MultiLine=true))
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FQuestStep> Steps;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FQuestReward Reward;

    // === C++-only helpers (not exposed to BP) ===
    const FQuestStep* FindStepById_Native(FName StepId) const
    {
        if (StepId.IsNone()) return nullptr;
        for (const FQuestStep& S : Steps)
        {
            if (S.StepId == StepId) return &S;
        }
        return nullptr;
    }

    const FQuestStep* GetFirstStep_Native() const
    {
        return Steps.Num() > 0 ? &Steps[0] : nullptr;
    }

    // === Blueprint-friendly wrappers ===
    UFUNCTION(BlueprintPure, Category="Quest")
    bool FindStepById(FName StepId, FQuestStep& OutStep) const
    {
        if (const FQuestStep* S = FindStepById_Native(StepId))
        {
            OutStep = *S;        // copy for BP
            return true;
        }
        return false;
    }

    UFUNCTION(BlueprintPure, Category="Quest")
    bool GetFirstStep(FQuestStep& OutStep) const
    {
        if (Steps.Num() > 0)
        {
            OutStep = Steps[0];  // copy for BP
            return true;
        }
        return false;
    }
};