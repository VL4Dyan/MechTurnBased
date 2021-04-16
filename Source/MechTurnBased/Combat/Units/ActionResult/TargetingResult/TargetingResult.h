// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MechComponent.h"
#include "../DataUpdate/TileDataUpdate.h"
#include "../DataUpdate/GridObjectComponentStateUpdate.h"
#include "TargetingResult.generated.h"


UCLASS(Abstract, Blueprintable)
class MECHTURNBASED_API UTargetingResult : public UObject
{
	GENERATED_BODY()

public:
	UTargetingResult();

	UFUNCTION()
		void ExecuteContainedUpdates();
	UFUNCTION()
		void SetExecutorComponent(UMechComponent* ExecutorComponentToSet);

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<UGridObjectComponentStateUpdate*> GridObjectComponentUpdates;
	UPROPERTY(BlueprintReadOnly)
		TArray<UTileDataUpdate*> TileUpdates;

protected:
	UPROPERTY()
		UMechComponent* ExecutorComponent = nullptr;
};
