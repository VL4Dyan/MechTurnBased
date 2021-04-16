// Fill out your copyright notice in the Description page of Project Settings.


#include "TileTargetingResult.h"

UTileTargetingResult::UTileTargetingResult()
{

}

void UTileTargetingResult::Initialize(FMatrixIndex TileIndexToSet)
{
	TileIndex = TileIndexToSet;
}

FMatrixIndex UTileTargetingResult::GetTileIndex()
{
	return TileIndex;
}

UTileDataUpdate* UTileTargetingResult::AddTileDataUpdate(FMatrixIndex AffectedTileIndex)
{
	UTileDataUpdate* TileUpdate = NewObject<UTileDataUpdate>();
	TileUpdate->Initialize(AffectedTileIndex);

	TileUpdates.Add(TileUpdate);

	return TileUpdate;
}
