// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PathfindingNode.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileData.h"
#include <vector>
#include "MatrixIndexes.h"
#include "../Units/CombatUnit.h"
#include "Components/BoxComponent.h"
#include "CombatGridManager.generated.h"

using namespace std;

UCLASS(Blueprintable)
class MECHTURNBASED_API UCombatGridManager : public UActorComponent
{
	GENERATED_BODY()

private:
	UFUNCTION()
		FMatrixIndexes CalculateSpawningPoint();
	UFUNCTION()
		TArray<UPathfindingNode*> GetNeighbors(UPathfindingNode* CurrentNode, FMatrixIndexes DestinationPoint);

public:
	UCombatGridManager();// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable)
		void BuildGrid();
	UFUNCTION(BlueprintCallable)
		bool GetTileDataByIndex(const FMatrixIndexes &indexes, FTileData &tileDataOut);
	UFUNCTION(BlueprintCallable)
		bool ConvertCoordinatesToIndexes(const FVector &coordinates, FMatrixIndexes &indexesOut);
	UFUNCTION(BlueprintCallable)
		bool AddCombatUnitOnBattlefield(ACombatUnit* combatUnit);
	UFUNCTION(BlueprintCallable)
		bool UpdateTileData(const FMatrixIndexes &indexes, FTileData tileData);
	UFUNCTION(BlueprintCallable)
		bool IsTileHolderInTileDataNull(FTileData tileData);
	UFUNCTION(BlueprintCallable)
		bool GetLocationsToMoveThrough(const FMatrixIndexes &startLocationIndexes, const FMatrixIndexes &endLocationIndexes, TArray<FVector> &vectorArrayOut);
	UFUNCTION(BlueprintCallable)
		bool SwapTileHolders(const FMatrixIndexes &tileOneIndexes, const FMatrixIndexes &tileTwoIndexes);

protected:
	virtual void BeginPlay() override;// Called when the game starts or when spawned

private:
	UFUNCTION()
		bool AreIndexesInRange(const FMatrixIndexes &indexes);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TileStep = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ScanRangeX = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ScanRangeY = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int ScanRangeZ = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMatrixIndexes SpawningPoint = FMatrixIndexes(0, 0, 0);

private:
	TArray<TArray<TArray<FTileData>>> GridMatrix;
};
