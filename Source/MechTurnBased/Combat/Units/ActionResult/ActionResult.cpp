// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionResult.h"

UActionResult::UActionResult()
{

}

UTileTargetingResult* UActionResult::AddTileTarget(TArray<FMatrixIndex> TargetTileIndex)
{
	UTileTargetingResult* TileTarget = NewObject<UTileTargetingResult>();
	TileTarget->Initialize(TargetTileIndex);

	TileTargetingResults.Add(TileTarget);

	return TileTarget;
}

void UActionResult::Initialize(UGridObjectComponent* ExecutorComponentToSet)
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
		Result.Append(TileTarget->GetTileIndexArray());
	}

	return Result;
}

TArray<UTargetingResult*> UActionResult::GetTargetingResultsByTile(FMatrixIndex TileTarget)
{
	TArray<UTargetingResult*> Result;

	for (UTileTargetingResult* TileTargetingResult : TileTargetingResults)
	{
		TArray<FMatrixIndex> TileIndexArray = TileTargetingResult->GetTileIndexArray();

		for (FMatrixIndex TileIndex : TileIndexArray)
		{
			if (TileIndex == TileTarget)
			{
				if (TileTargetingResult->GridObjectComponentUpdates.Num() > 0 || TileTargetingResult->TileUpdates.Num() > 0)
				{
					Result.Add(TileTargetingResult);
				}

				for (UComponentTargetingResult* CompTargetingResult : TileTargetingResult->ComponentTargetingResults)
				{
					Result.Add(CompTargetingResult);
				}

				return Result;
			}
		}
	}

	return Result;
}

