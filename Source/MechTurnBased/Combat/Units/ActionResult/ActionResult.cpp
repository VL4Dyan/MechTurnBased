// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionResult.h"

UActionResult::UActionResult()
{

}

UTileTargetingResult* UActionResult::AddTileTarget(FMatrixIndex TargetTileIndex)
{
	UTileTargetingResult* TileTargetingRes = NewObject<UTileTargetingResult>();
	TileTargetingRes->SetExecutorComponent(ExecutorComponent);

	TileTargetingRes->Initialize(TargetTileIndex);

	TileTargetingResults.Add(TileTargetingRes);

	return TileTargetingRes;
}

UGridObjectTargetingResult* UActionResult::AddGridObjectTarget(AGridObject* TargetGridObject)
{
	UGridObjectTargetingResult* GridObjTargetingRes = NewObject<UGridObjectTargetingResult>();
	GridObjTargetingRes->SetExecutorComponent(ExecutorComponent);

	GridObjTargetingRes->Initialize(TargetGridObject);

	GridObjectTargetingResults.Add(GridObjTargetingRes);

	return GridObjTargetingRes;
}

void UActionResult::Initialize(UMechComponent* ExecutorComponentToSet)
{
	ExecutorComponent = ExecutorComponentToSet;
}

FComponentDescription UActionResult::GetComponentDescription()
{
	FComponentDescription Result = FComponentDescription();

	if (ExecutorComponent != nullptr)
	{
		Result.ComponentType = ExecutorComponent->GetComponentType();
	}

	return Result;
}

TArray<FMatrixIndex> UActionResult::GetTilesToHighlight()
{
	TArray<FMatrixIndex> Result;

	for (UTileTargetingResult* TileTarget : TileTargetingResults)
	{
		Result.Add(TileTarget->GetTileIndex());
	}

	return Result;
}

TArray<UTargetingResult*> UActionResult::GetTargetingResultsByTile(FMatrixIndex TileTarget)
{
	TArray<UTargetingResult*> Result;

	for (UTileTargetingResult* TileTargetingRes : TileTargetingResults)
	{
		if (TileTargetingRes->TileIndex == TileTarget)
		{
			Result.Add(TileTargetingRes);

			return Result;
		}
	}

	for (UGridObjectTargetingResult* GridObjTargetingRes : GridObjectTargetingResults)
	{
		TArray<FMatrixIndex> TilesOccupiedByGridObject = GridObjTargetingRes->GridObject->GetOccupiedTiles();

		if (TilesOccupiedByGridObject.Contains(TileTarget))
		{
			Result.Add(GridObjTargetingRes);
			Result.Append(GridObjTargetingRes->ComponentTargetingResults);

			break;
		}
	}

	return Result;
}

void UActionResult::GetUpdatesToProcess(TArray<UTileDataUpdate*>& OutTileDataUpdates, TArray<UGridObjectComponentStateUpdate*>& OutGridObjCompStateUpdates)
{
	for (UTileTargetingResult* TileTargetingRes : TileTargetingResults)
	{
		OutTileDataUpdates.Append(TileTargetingRes->TileUpdates);
		OutGridObjCompStateUpdates.Append(TileTargetingRes->GridObjectComponentUpdates);
	}

	for (UGridObjectTargetingResult* GridObjTargetingRes : GridObjectTargetingResults)
	{
		OutTileDataUpdates.Append(GridObjTargetingRes->TileUpdates);
		OutGridObjCompStateUpdates.Append(GridObjTargetingRes->GridObjectComponentUpdates);

		for (UTargetingResult* GridObjCompTargetingRes : GridObjTargetingRes->ComponentTargetingResults)
		{
			OutTileDataUpdates.Append(GridObjCompTargetingRes->TileUpdates);
			OutGridObjCompStateUpdates.Append(GridObjCompTargetingRes->GridObjectComponentUpdates);
		}
	}
}
