// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Quests/QuestDataAsset.h"
#include "KoEQuestGiverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KINGDOMOFENOCH_API UKoEQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quests")
    TArray<TObjectPtr<UQuestDataAsset>> QuestsToStart;

    UFUNCTION(BlueprintCallable, Category="Quests")
    void GiveQuestsTo(APawn* Pawn);
};
