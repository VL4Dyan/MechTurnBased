// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMode.h"

void ACombatMode::ScanGrid(ATileChecker* TileChecker)
{
	CombatGridManager = NewObject<UCombatGridManager>();
	CombatGridManager->BuildGrid();
	int scanRangeX, scanRangeY, scanRangeZ;
	float tileStep = CombatGridManager->TileStep;
	scanRangeX = CombatGridManager->ScanRangeX;
	scanRangeY = CombatGridManager->ScanRangeY;
	scanRangeZ = CombatGridManager->ScanRangeZ;

	for (int IndexX = 0; IndexX < scanRangeX; IndexX++)
	{
		for (int IndexY = 0; IndexY < scanRangeY; IndexY++)
		{
			for (int IndexZ = 0; IndexZ < scanRangeZ; IndexZ++)
			{
				FMatrixIndex Index(IndexX, IndexY, IndexZ);
				FTileData CurrentTile;
				CombatGridManager->TryGetTileDataByIndex(Index, CurrentTile);
				TileChecker->SetActorLocation(CurrentTile.AbsoluteCoordinates);
				CurrentTile = TileChecker->Scan(CurrentTile);

				if (CurrentTile.SpawnPoint != nullptr)
				{
					CurrentTile.SpawnPoint->TileIndex = Index;
					SpawnPoints.Add(CurrentTile.SpawnPoint);
				}

				CombatGridManager->TryUpdateTileData(Index, CurrentTile);
			}
		}
	}
}

bool ACombatMode::PlaceCombatUnitOnGrid(ACombatUnit* CombatUnit, ASpawnPoint* SpawnPoint)
{
	FMatrixIndex ResultingSpawnPoint;
	bool bFunctionSuccess = false;

	if (CombatGridManager->TryGetUnoccupiedTileAroundSpawnPoint(SpawnPoint->TileIndex, ResultingSpawnPoint))
	{
		FTileData TileDataToUpdate;
		if (CombatGridManager->TryGetTileDataByIndex(ResultingSpawnPoint, TileDataToUpdate))
		{
			TileDataToUpdate.TileHolder = Cast<AGridObject>(CombatUnit);
			CombatUnit->UnitTileIndex = ResultingSpawnPoint;
			CombatUnit->SetActorLocation(TileDataToUpdate.AbsoluteCoordinates);
			CombatUnit->UnitOwner = SpawnPoint->Team;

			if (CombatGridManager->TryUpdateTileData(ResultingSpawnPoint, TileDataToUpdate))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

UCombatGridManager* ACombatMode::GetCombatGridManagerRef()
{
	return CombatGridManager;
}