// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KoEHUD.generated.h"

class UKoEMainHUDWidget;
class UQuestLogComponent;

UCLASS()
class KINGDOMOFENOCH_API AKoEHUD : public AHUD
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category="UI")
    TSubclassOf<UKoEMainHUDWidget> MainHUDClass;

protected:
    UPROPERTY()
    TObjectPtr<UKoEMainHUDWidget> MainHUD;

    UPROPERTY()
    TObjectPtr<UQuestLogComponent> QuestLogRef;

    UFUNCTION()
    void HandleQuestUpdated(const FQuestRuntime& Quest);

    UFUNCTION()
    void HandleObjectiveUpdated(FPrimaryAssetId QuestId, FName ObjectiveId, const FObjectiveRuntime& Runtime);
};
