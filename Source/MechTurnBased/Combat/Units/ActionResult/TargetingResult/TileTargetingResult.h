// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Grid/MatrixIndex.h"
#include "ComponentTargetingResult.h"
#include "../DataUpdate/GridObjectComponentStateUpdate.h"
#include "../DataUpdate/TileDataUpdate.h"
#include "TargetingResult.h"
#include "TileTargetingResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UTileTargetingResult : public UTargetingResult
{
	GENERATED_BODY()

public:
	UTileTargetingResult();

	UFUNCTION()
		void Initialize(FMatrixIndex TileIndexToSet);
	UFUNCTION()
		FMatrixIndex GetTileIndex();
	UFUNCTION()
		UTileDataUpdate* AddTileDataUpdate(FMatrixIndex AffectedTileIndex);

public:
	UPROPERTY()
		FMatrixIndex TileIndex;
};