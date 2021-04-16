// Fill out your copyright notice in the Description page of Project Settings.

#include "TileDataUpdate.h"
#include "../../../Grid/CombatGridManager.h"
#include "../../../CombatMode.h"

UTileDataUpdate::UTileDataUpdate()
{

}

void UTileDataUpdate::Initialize(FMatrixIndex TileIndexToSet)
{
	UCombatGridManager* CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();

	TileIndex = TileIndexToSet;

	if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, OldTileData))
	{
		bCorrectParameters = true;
		TileDataReplacement = OldTileData;
	}
}

void UTileDataUpdate::SetTileDataReplacement(FTileData TileDataReplacementToSet)
{
	TileDataReplacement = TileDataReplacementToSet;
}

void UTileDataUpdate::ExecuteUpdate()
{
	if (bCorrectParameters)
	{
		UCombatGridManager* CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();

		CombatGridManagerRef->TryUpdateTileData(TileIndex, TileDataReplacement);
	}
}

void UTileDataUpdate::GetCurrentTileInfo(FMatrixIndex& OutTileIndex, FTileData& OutTileData)
{
	OutTileIndex = TileIndex;
	OutTileData = OldTileData;
}