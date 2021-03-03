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
		UTileTargetingResult* AddTileTarget(FMatrixIndex TargetTileIndex);
	UFUNCTION()
		UComponentTargetingResult* AddComponentTarget(UGridObjectComponent* GridObjectComponentRef);

private:
	TArray<UTileTargetingResult*> TileTargetingResults;
	TArray<UComponentTargetingResult*> ComponentTargetingResults;
};
