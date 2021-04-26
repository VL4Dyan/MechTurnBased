// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileData.h"
#include <vector>
#include "MatrixIndex.h"
#include "../GridObjects/GridObject.h"
#include "Components/BoxComponent.h"
#include "CombatGridManager.generated.h"

using namespace std;

UCLASS(Blueprintable)
class MECHTURNBASED_API UCombatGridManager : public UObject
{
	GENERATED_BODY()

private:
	bool IsIndexInRange(const FMatrixIndex& Indexes);
	bool AreValuesInRange(const int& IndexX, const int& IndexY, const int& IndexZ);

public:
	UCombatGridManager();// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable)
		void BuildGrid();
	UFUNCTION(BlueprintCallable)
		bool TryGetTileDataByIndex(const FMatrixIndex& Index, FTileData& OutTileData);
	UFUNCTION(BlueprintCallable)
		FMatrixIndex ConvertCoordinatesToIndexes(const FVector& Coordinates);
	UFUNCTION(BlueprintCallable)
		bool TryUpdateTileData(const FMatrixIndex& Index, FTileData TileData);
	UFUNCTION(BlueprintCallable)
		bool IsTileHolderInTileDataNull(FTileData TileData);
	UFUNCTION(BlueprintCallable)
		bool SwapTileHolders(const FMatrixIndex& TileOneIndex, const FMatrixIndex& TileTwoIndexes);
	UFUNCTION()
		bool TryGetUnoccupiedTileAroundSpawnPoint(FMatrixIndex SpawnPointIndex, FMatrixIndex& OutTileIndex);
	UFUNCTION()
		void GetTileMeasurments(float& OutTileWidthLength, float& OutTileHeight);

public:
	UPROPERTY()
		float TileStep = 100;
	UPROPERTY()
		float TileHeight = 100;
	UPROPERTY(BlueprintReadWrite)
		int ScanRangeX = 20;
	UPROPERTY(BlueprintReadWrite)
		int ScanRangeY = 20;
	UPROPERTY(BlueprintReadWrite)
		int ScanRangeZ = 10;

private:
	TArray<TArray<TArray<FTileData>>> GridMatrix; //The matrix structure should be changed; GC is not covering this
};
