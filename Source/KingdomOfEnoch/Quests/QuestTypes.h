// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "QuestTypes.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    NotStarted UMETA(DisplayName="Not Started"),
    InProgress UMETA(DisplayName="In Progress"),
    Completed  UMETA(DisplayName="Completed"),
    Failed     UMETA(DisplayName="Failed")
};

UENUM(BlueprintType)
enum class EObjectiveStatus : uint8
{
    Hidden   UMETA(DisplayName="Hidden"),
    Active   UMETA(DisplayName="Active"),
    Success  UMETA(DisplayName="Success"),
    Failed   UMETA(DisplayName="Failed")
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    // Unique within a quest
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ObjectiveId = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Description;

    // Optional gameplay tag to listen for (e.g. "Quest.Obtained.IronNails")
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag ProgressEventTag;

    // Target count for counters (0/1 treated as boolean)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 TargetCount = 1;

    // If true, this objective does not block step completion
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bOptional = false;
};

USTRUCT(BlueprintType)
struct FQuestStep
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName StepId = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText StepTitle;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FQuestObjective> Objectives;

    // If set, automatically move to this step on completion
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName NextStepId = NAME_None;
};

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 XP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Gold = 0;
};

// Runtime state for one objective
USTRUCT(BlueprintType)
struct FObjectiveRuntime
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName ObjectiveId = NAME_None;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentCount = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EObjectiveStatus Status = EObjectiveStatus::Hidden;
};

// Runtime state for an entire quest
USTRUCT(BlueprintType)
struct FQuestRuntime
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FPrimaryAssetId QuestAssetId; // Points to UQuestDataAsset

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EQuestStatus Status = EQuestStatus::NotStarted;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName ActiveStepId = NAME_None;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FObjectiveRuntime> Objectives; // Mirrors active step
};