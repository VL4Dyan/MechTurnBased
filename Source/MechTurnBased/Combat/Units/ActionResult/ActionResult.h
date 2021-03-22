// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GridObjects/GridObjectComponent.h"
#include "../../Grid/MatrixIndex.h"
#include "ComponentDescription.h"
#include "TileTargetingResult.h"
#include "ComponentTargetingResult.h"
#include "TargetingResult.h"
#include "ActionResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UActionResult : public UObject
{
	GENERATED_BODY()

public:
	UActionResult();

	UFUNCTION()
		UTileTargetingResult* AddTileTarget(TArray<FMatrixIndex> TargetTileIndex);
	UFUNCTION()
		void Initialize(UGridObjectComponent* ExecutorComponentToSet);
	UFUNCTION(BlueprintCallable)
		FComponentDescription GetComponentDescription();
	//UFUNCTION(BlueprintCallable)
	//	void GetExecutorComponentGeneralInfo();
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetTilesToHighlight();
	UFUNCTION(BlueprintCallable)
		TArray<UTargetingResult*> GetTargetingResultsByTile(FMatrixIndex TileTarget);

public:
	UPROPERTY(BlueprintReadWrite)
		UGridObjectComponent* ExecutorComponent = nullptr;

private:
	UPROPERTY()
		TArray<UTileTargetingResult*> TileTargetingResults;

};
