// Fill out your copyright notice in the Description page of Project Settings.


#include "TileTargetingResult.h"

UTileTargetingResult::UTileTargetingResult()
{

}

void UTileTargetingResult::Initialize(TArray<FMatrixIndex> TileIndexArrayToSet)
{
	TileIndexArray = TileIndexArrayToSet;
}

UComponentTargetingResult* UTileTargetingResult::AddComponentTarget(UGridObjectComponent* GridObjectComponentTarget)
{
	UComponentTargetingResult* ComponentTarget = NewObject<UComponentTargetingResult>();
	ComponentTarget->Initialize(GridObjectComponentTarget);

	ComponentTargetingResults.Add(ComponentTarget);

	return ComponentTarget;
}

TArray<FMatrixIndex> UTileTargetingResult::GetTileIndexArray()
{
	return TileIndexArray;
}

UTileDataUpdate* UTileTargetingResult::AddTileDataUpdate(FMatrixIndex TileIndex)
{
	UTileDataUpdate* TileUpdate = NewObject<UTileDataUpdate>();
	TileUpdate->Initialize(TileIndex);

	TileUpdates.Add(TileUpdate);

	return TileUpdate;
}


