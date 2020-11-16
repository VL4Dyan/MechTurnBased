// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMode.h"

void ACombatMode::ScanGrid(UCombatGridManager* combatGridManager, ATileChecker* tileChecker)
{
	combatGridManager->BuildGrid();
	int scanRangeX, scanRangeY, scanRangeZ;
	float tileStep = combatGridManager->TileStep;
	scanRangeX = combatGridManager->ScanRangeX;
	scanRangeY = combatGridManager->ScanRangeY;
	scanRangeZ = combatGridManager->ScanRangeZ;

	for (int indexX = 0; indexX < scanRangeX; indexX++)
	{
		for (int indexY = 0; indexY < scanRangeY; indexY++)
		{
			for (int indexZ = 0; indexZ < scanRangeZ; indexZ++)
			{
				FMatrixIndexes indexes(indexX, indexY, indexZ);
				FTileData currentTile;
				combatGridManager->GetTileDataByIndex(indexes, currentTile);
				tileChecker->SetActorLocation(currentTile.AbsoluteCoordinates);

				//Log message starts here
				//FVector vector = tileChecker->GetActorLocation();
				//FString msg = vector.ToString();
				//UE_LOG(LogTemp, Warning, TEXT("Checked space: %s"), *msg);
				//Log message ends here

				currentTile = tileChecker->Scan(currentTile);
				combatGridManager->UpdateTileData(indexes, currentTile);
			}
		}
	}
}