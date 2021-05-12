// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UMechComponent;
class UTileDataUpdate;
class UGridObjectComponentStateUpdate;

#include "../../Grid/MatrixIndex.h"
#include "ComponentDescription.h"
#include "TargetingResult/TileTargetingResult.h"
#include "TargetingResult/GridObjectTargetingResult.h"
#include "TargetingResult/ComponentTargetingResult.h"
#include "TargetingResult/TargetingResult.h"
#include "ActionResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UActionResult : public UObject
{
	GENERATED_BODY()

public:
	UActionResult();

	UFUNCTION(BlueprintCallable)
		void Initialize(UMechComponent* ExecutorComponentToSet);
	UFUNCTION(BlueprintCallable)
		UTileTargetingResult* AddTileTarget(FMatrixIndex TargetTileIndex);
	UFUNCTION(BlueprintCallable)
		UGridObjectTargetingResult* AddGridObjectTarget(AGridObject* TargetGridObject);
	UFUNCTION(BlueprintCallable)
		void GetUpdatesToProcess(TArray<UTileDataUpdate*>& OutTileDataUpdates, TArray<UGridObjectComponentStateUpdate*>& OutGridObjCompStateUpdates);
	UFUNCTION(BlueprintCallable)
		FComponentDescription GetComponentDescription();
	//UFUNCTION(BlueprintCallable)
	//	void GetExecutorComponentGeneralInfo();
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetTilesToHighlight();
	UFUNCTION(BlueprintCallable)
		TArray<UTargetingResult*> GetTargetingResultsByTile(FMatrixIndex TileTarget);

private:
	UPROPERTY()
		TArray<UGridObjectTargetingResult*> GridObjectTargetingResults;
	UPROPERTY()
		TArray<UTileTargetingResult*> TileTargetingResults;
	UPROPERTY()
		UMechComponent* ExecutorComponent = nullptr;
};
