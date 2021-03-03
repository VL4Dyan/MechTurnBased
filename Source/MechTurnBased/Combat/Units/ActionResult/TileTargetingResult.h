// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "../../Grid/MatrixIndex.h"
#include "ComponentTargetingResult.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "TileTargetingResult.generated.h"

UCLASS()
class MECHTURNBASED_API UTileTargetingResult : public UObject
{
	GENERATED_BODY()

public:
	UTileTargetingResult();

	UFUNCTION()
		void Initialize(FMatrixIndex TileIndexToSet);

public:
	UPROPERTY()
		FMatrixIndex TileIndex;
	UPROPERTY()
		TArray<UGridObjectComponentStateUpdate*> MechComponentUpdates;
	UPROPERTY()
		TArray<UTileDataUpdate*> TileUpdates;
};