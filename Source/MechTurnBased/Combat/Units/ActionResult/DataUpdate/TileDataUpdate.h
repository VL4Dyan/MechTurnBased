// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Grid/TileData.h"
#include "../../../Grid/MatrixIndex.h"
#include "TileDataUpdate.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UTileDataUpdate : public UObject
{
	GENERATED_BODY()

public:
	UTileDataUpdate();

	UFUNCTION()
		void Initialize(FMatrixIndex TileIndexToSet);
	UFUNCTION(BlueprintCallable)
		void GetCurrentTileInfo(FMatrixIndex& OutTileIndex, FTileData& OutTileData);
	UFUNCTION(BlueprintCallable)
		void SetTileDataReplacement(FTileData TileDataReplacementToSet);
	UFUNCTION()
		void ExecuteUpdate();

private:
	UPROPERTY()
		bool bCorrectParameters = false;
	UPROPERTY()
		FMatrixIndex TileIndex;
	UPROPERTY()
		FTileData TileDataReplacement;
	UPROPERTY()
		FTileData OldTileData;
};
