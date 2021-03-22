// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "../../Grid/MatrixIndex.h"
#include "ComponentTargetingResult.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "TargetingResult.h"
#include "TileTargetingResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UTileTargetingResult : public UTargetingResult
{
	GENERATED_BODY()

public:
	UTileTargetingResult();

	UFUNCTION()
		void Initialize(TArray<FMatrixIndex> TileIndexArrayToSet);
	UFUNCTION()
		UComponentTargetingResult* AddComponentTarget(UGridObjectComponent* GridObjectComponentTarget);
	UFUNCTION()
		TArray<FMatrixIndex> GetTileIndexArray();
	UFUNCTION()
		UTileDataUpdate* AddTileDataUpdate(FMatrixIndex TileIndex);

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<UGridObjectComponentStateUpdate*> GridObjectComponentUpdates;
	UPROPERTY(BlueprintReadOnly)
		TArray<UTileDataUpdate*> TileUpdates;
	UPROPERTY()
		TArray<FMatrixIndex> TileIndexArray;
	UPROPERTY()
		TArray<UComponentTargetingResult*> ComponentTargetingResults;

};