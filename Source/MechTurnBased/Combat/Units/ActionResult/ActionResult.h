// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentTargetingResult.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "TileTargetingResult.h"
#include "ComponentTargetingResult.h"
#include "../../Grid/MatrixIndex.h"
#include "ActionResult.generated.h"

UCLASS()
class MECHTURNBASED_API UActionResult : public UObject
{
	GENERATED_BODY()

public:
	UActionResult();

	UFUNCTION()
		void AddTileTarget(FMatrixIndex TileIndex);
	UFUNCTION()
		void AddComponentTarget(FMatrixIndex TileIndexOfExistingTileTarget, UGridObjectComponent* MechComponent);
	UFUNCTION()
		bool TryCreateCompUpdate(UGridObjectComponent* MechComponentToAdd, FMatrixIndex TargetTileIndex, UGridObjectComponent* TargetMechComponent = nullptr);
	UFUNCTION()
		bool TryCreateTileUpdate(FMatrixIndex TileIndexToAdd, FMatrixIndex TargetTileIndex, UGridObjectComponent* TargetMechComponent = nullptr);
	UFUNCTION()
		TArray<UGridObjectComponentStateUpdate*> GetComponentStateUpdates();

private:
	TArray<UTileTargetingResult*> TileTargets;
};
