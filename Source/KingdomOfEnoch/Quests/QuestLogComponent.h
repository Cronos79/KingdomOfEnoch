#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StreamableManager.h"
#include "QuestTypes.h"
#include "QuestDataAsset.h"
#include "QuestLogComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, const FQuestRuntime&, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectiveUpdated, FPrimaryAssetId, QuestId, FName, ObjectiveId, const FObjectiveRuntime&, Runtime);

UCLASS(ClassGroup=(Gameplay), meta=(BlueprintSpawnableComponent))
class UQuestLogComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UQuestLogComponent();

    UPROPERTY(BlueprintAssignable)
    FOnQuestUpdated OnQuestUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnObjectiveUpdated OnObjectiveUpdated;

    // Begin UActorComponent
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    // End UActorComponent

    // Start or fetch quest by asset id (e.g. from PrimaryAsset path or soft reference)
    UFUNCTION(BlueprintCallable)
    bool StartQuest(UQuestDataAsset* QuestAsset);

    UFUNCTION(BlueprintCallable)
    bool AbandonQuest(FPrimaryAssetId QuestAssetId);

    UFUNCTION(BlueprintCallable)
    bool CompleteActiveStep(FPrimaryAssetId QuestAssetId);

    UFUNCTION(BlueprintCallable)
    bool AddObjectiveProgressByTag(const FGameplayTag& EventTag, int32 Amount = 1);

    UFUNCTION(BlueprintCallable)
    FQuestRuntime GetQuestRuntime(FPrimaryAssetId QuestAssetId) const;

    UFUNCTION(BlueprintCallable)
    TArray<FQuestRuntime> GetAllQuests() const { return ActiveQuests; }

    UFUNCTION(BlueprintCallable)
    void GetQuestUIData(UObject* WorldContextObject,
        FPrimaryAssetId QuestId,
        FText& OutQuestName,
        FText& OutQuestDescription,
        FText& OutStepTitle,
        TArray<FText>& OutObjectiveDescriptions,
        TArray<int32>& OutCurrentCounts,
        TArray<int32>& OutTargetCounts,
        TArray<EObjectiveStatus>& OutStatuses) const;

protected:
    UPROPERTY(Replicated, VisibleAnywhere)
    TArray<FQuestRuntime> ActiveQuests;

    UPROPERTY()
    TMap<FPrimaryAssetId, TObjectPtr<UQuestDataAsset>> LoadedQuestAssets;

    // Helpers
    FQuestRuntime* FindQuestRuntimeMutable(FPrimaryAssetId Id);
    const UQuestDataAsset* GetQuestAsset(FPrimaryAssetId Id) const;

    void InitializeStepRuntime(FQuestRuntime& QuestState, const FQuestStep& StepDef);
    bool AreBlockingObjectivesComplete(const FQuestRuntime& QuestState, const FQuestStep& StepDef) const;
};
