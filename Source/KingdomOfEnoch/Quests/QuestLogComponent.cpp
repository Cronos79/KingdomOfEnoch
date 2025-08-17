#include "QuestLogComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/AssetManager.h"

UQuestLogComponent::UQuestLogComponent()
{
    SetIsReplicatedByDefault(true);
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestLogComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UQuestLogComponent, ActiveQuests);
}

const UQuestDataAsset* UQuestLogComponent::GetQuestAsset(FPrimaryAssetId Id) const
{
    if (const TObjectPtr<UQuestDataAsset>* Found = LoadedQuestAssets.Find(Id))
    {
        return Found->Get();
    }
    return nullptr;
}

FQuestRuntime* UQuestLogComponent::FindQuestRuntimeMutable(FPrimaryAssetId Id)
{
    for (FQuestRuntime& R : ActiveQuests)
    {
        if (R.QuestAssetId == Id)
            return &R;
    }
    return nullptr;
}

bool UQuestLogComponent::StartQuest(UQuestDataAsset* QuestAsset)
{
    if (!QuestAsset) return false;

    FPrimaryAssetId Id = QuestAsset->GetPrimaryAssetId();

    // Already in log?
    if (FindQuestRuntimeMutable(Id)) return true;

    FQuestRuntime NewState;
    NewState.QuestAssetId = Id;
    NewState.Status = EQuestStatus::InProgress;

    FQuestStep FirstStep;
    if (!QuestAsset->GetFirstStep(FirstStep)) return false;
    NewState.ActiveStepId = FirstStep.StepId;
    InitializeStepRuntime(NewState, FirstStep);

    ActiveQuests.Add(MoveTemp(NewState));
    OnQuestUpdated.Broadcast(GetQuestRuntime(Id));
    return true;
}

void UQuestLogComponent::InitializeStepRuntime(FQuestRuntime& QuestState, const FQuestStep& StepDef)
{
    QuestState.Objectives.Empty();
    for (const FQuestObjective& Obj : StepDef.Objectives)
    {
        FObjectiveRuntime RT;
        RT.ObjectiveId = Obj.ObjectiveId;
        RT.Status = EObjectiveStatus::Active; // reveal on start
        QuestState.Objectives.Add(RT);
    }
}

bool UQuestLogComponent::AreBlockingObjectivesComplete(const FQuestRuntime& QuestState, const FQuestStep& StepDef) const
{
    for (int32 i = 0; i < StepDef.Objectives.Num(); ++i)
    {
        const FQuestObjective& Def = StepDef.Objectives[i];
        const FObjectiveRuntime& RT = QuestState.Objectives.IsValidIndex(i) ? QuestState.Objectives[i] : FObjectiveRuntime();

        if (Def.bOptional) continue;
        if (RT.Status != EObjectiveStatus::Success)
        {
            return false;
        }
    }
    return true;
}

bool UQuestLogComponent::CompleteActiveStep(FPrimaryAssetId QuestAssetId)
{
    FQuestRuntime* State = FindQuestRuntimeMutable(QuestAssetId);
    if (!State) return false;

    const UQuestDataAsset* Asset = GetQuestAsset(QuestAssetId);
    if (!Asset) return false;

    FQuestStep Step;
    if (!Asset->FindStepById(State->ActiveStepId, Step)) return false;
    if (!AreBlockingObjectivesComplete(*State, Step)) return false;

    if (!Step.NextStepId.IsNone())
    {
        FQuestStep Next;
        if (!Asset->FindStepById(Step.NextStepId, Next)) return false;
        State->ActiveStepId = Next.StepId;
        InitializeStepRuntime(*State, Next);

        OnQuestUpdated.Broadcast(*State);
        return true;
    }

    State->Status = EQuestStatus::Completed;
    OnQuestUpdated.Broadcast(*State);
    return true;
}

bool UQuestLogComponent::AddObjectiveProgressByTag(const FGameplayTag& EventTag, int32 Amount)
{
    bool bAnyUpdated = false;

    for (FQuestRuntime& Q : ActiveQuests)
    {
        if (Q.Status != EQuestStatus::InProgress) continue;

        const UQuestDataAsset* Asset = GetQuestAsset(Q.QuestAssetId);
        if (!Asset) continue;

        // OLD:
        // const FQuestStep* Step = Asset->FindStepById(Q.ActiveStepId);
        // if (!Step) continue;

        // NEW:
        FQuestStep Step;
        if (!Asset->FindStepById(Q.ActiveStepId, Step)) continue;

        for (int32 i = 0; i < Step.Objectives.Num(); ++i)
        {
            const FQuestObjective& Def = Step.Objectives[i];
            FObjectiveRuntime& RT = Q.Objectives[i];

            if (Def.ProgressEventTag.IsValid() && Def.ProgressEventTag == EventTag && RT.Status == EObjectiveStatus::Active)
            {
                RT.CurrentCount = FMath::Clamp(RT.CurrentCount + Amount, 0, Def.TargetCount);
                if (RT.CurrentCount >= Def.TargetCount)
                {
                    RT.Status = EObjectiveStatus::Success;
                }
                OnObjectiveUpdated.Broadcast(Q.QuestAssetId, RT.ObjectiveId, RT);
                bAnyUpdated = true;
            }
        }

        // Auto-advance if all blocking complete and there is a NextStepId
        if (bAnyUpdated && AreBlockingObjectivesComplete(Q, Step) && !Step.NextStepId.IsNone())
        {
            CompleteActiveStep(Q.QuestAssetId);
        }
    }

    return bAnyUpdated;
}

bool UQuestLogComponent::AbandonQuest(FPrimaryAssetId QuestAssetId)
{
    for (int32 i = 0; i < ActiveQuests.Num(); ++i)
    {
        if (ActiveQuests[i].QuestAssetId == QuestAssetId)
        {
            ActiveQuests.RemoveAt(i);
            return true;
        }
    }
    return false;
}

FQuestRuntime UQuestLogComponent::GetQuestRuntime(FPrimaryAssetId QuestAssetId) const
{
    for (const FQuestRuntime& R : ActiveQuests)
    {
        if (R.QuestAssetId == QuestAssetId)
        {
            return R;
        }
    }
    return FQuestRuntime();
}

void UQuestLogComponent::GetQuestUIData(UObject* WorldContextObject, FPrimaryAssetId QuestId, FText& OutQuestName, FText& OutQuestDescription, FText& OutStepTitle, TArray<FText>& OutObjectiveDescriptions, TArray<int32>& OutCurrentCounts, TArray<int32>& OutTargetCounts, TArray<EObjectiveStatus>& OutStatuses) const
{
    OutQuestName = FText::GetEmpty();
    OutQuestDescription = FText::GetEmpty();
    OutStepTitle = FText::GetEmpty();
    OutObjectiveDescriptions.Reset();
    OutCurrentCounts.Reset();
    OutTargetCounts.Reset();
    OutStatuses.Reset();

    const UQuestDataAsset* Asset = GetQuestAsset(QuestId);

    // Fallback: load from Asset Manager if not cached
    if (!Asset)
    {
        if (UAssetManager* AM = UAssetManager::GetIfValid())
        {
            const FSoftObjectPath Path = AM->GetPrimaryAssetPath(QuestId);
            if (Path.IsValid())
            {
                if (UObject* Obj = Path.TryLoad())
                {
                    Asset = Cast<UQuestDataAsset>(Obj);
                    if (Asset)
                    {
                        const_cast<UQuestLogComponent*>(this)->LoadedQuestAssets.Add(QuestId, const_cast<UQuestDataAsset*>(Asset));
                    }
                }
            }
        }
    }

    if (!Asset)
    {
        return; // No data available
    }

    OutQuestName = Asset->DisplayName;
    OutQuestDescription = Asset->Description;

    const FQuestRuntime Runtime = GetQuestRuntime(QuestId);
    if (Runtime.Status == EQuestStatus::NotStarted)
    {
        FQuestStep First;
        if (Asset->GetFirstStep(First))
        {
            OutStepTitle = First.StepTitle;
            for (const FQuestObjective& Obj : First.Objectives)
            {
                OutObjectiveDescriptions.Add(Obj.Description);
                OutCurrentCounts.Add(0);
                OutTargetCounts.Add(Obj.TargetCount);
                OutStatuses.Add(EObjectiveStatus::Hidden);
            }
        }
        return;
    }

    // Active or completed step
    FQuestStep Step;
    if (Asset->FindStepById(Runtime.ActiveStepId, Step))
    {
        OutStepTitle = Step.StepTitle;
        for (int32 i = 0; i < Step.Objectives.Num(); ++i)
        {
            const FQuestObjective& Def = Step.Objectives[i];
            OutObjectiveDescriptions.Add(Def.Description);

            if (Runtime.Objectives.IsValidIndex(i))
            {
                const FObjectiveRuntime& OR = Runtime.Objectives[i];
                OutCurrentCounts.Add(OR.CurrentCount);
                OutTargetCounts.Add(Def.TargetCount);
                OutStatuses.Add(OR.Status);
            }
            else
            {
                OutCurrentCounts.Add(0);
                OutTargetCounts.Add(Def.TargetCount);
                OutStatuses.Add(EObjectiveStatus::Hidden);
            }
        }
    }
}
