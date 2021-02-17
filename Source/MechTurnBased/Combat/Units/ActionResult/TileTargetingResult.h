// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ComponentTargetingResult.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "TileTargetingResult.generated.h"

UCLASS(Blueprintable)
class MECHTURNBASED_API UTileTargetingResult : public UObject
{
	GENERATED_BODY()

public:
	UTileTargetingResult();

	UFUNCTION()
		void Initialize(FMatrixIndex TileIndexToSet);

public:
	UPROPERTY(BlueprintReadOnly)
		FMatrixIndex TileIndex;
	UPROPERTY(BlueprintReadOnly)
		TArray<UComponentTargetingResult*> ComponentTargetResults;	//Results that are based on specific component pick

	UPROPERTY(BlueprintReadOnly)										//
		TArray<UGridObjectComponentStateUpdate*> MechComponentUpdates;	//
	UPROPERTY(BlueprintReadOnly)										//
		TArray<UTileDataUpdate*>  TileUpdates;							//These arrays contain updates if picking just this tile should output a result
};
