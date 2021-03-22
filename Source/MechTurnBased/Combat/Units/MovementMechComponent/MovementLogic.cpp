// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementLogic.h"

UMovementLogic::UMovementLogic()
{

}

UActionResult* UMovementLogic::GetActionResult(FMatrixIndex StartTile, int Distance)
{
	UActionResult* Result = NewObject<UActionResult>();

	TArray<FMatrixIndex> EndLocations = GetAllEndLocations(StartTile, Distance);
	
	for (FMatrixIndex TileIndex : EndLocations)
	{
		TArray<FMatrixIndex> TileIndexArray;
		TileIndexArray.Add(TileIndex);

		Result->AddTileTarget(TileIndexArray);
	}

	return Result;
}

TArray<FMatrixIndex> UMovementLogic::GetAllEndLocations(FMatrixIndex StartingTile, int Distance)
{
	TArray<FMatrixIndex> Result;
	int MovesLeft = Distance;
	int CurrentArrayStartingIndex = 0, CurrentArrayEndingIndex = 0;
	Result.Add(StartingTile);
	CurrentArrayEndingIndex = Result.Num();

	while (MovesLeft > 0 && CurrentArrayStartingIndex != CurrentArrayEndingIndex)
	{
		MovesLeft--;

		for (int i = CurrentArrayStartingIndex; i < CurrentArrayEndingIndex; i++)
		{
			TArray<FMatrixIndex> TempIndexesArray = GetNeighbouringTiles(Result[i]);

			for (int j = 0; j < TempIndexesArray.Num(); j++)
			{
				if (!Result.Contains(TempIndexesArray[j]))
				{
					Result.Add(TempIndexesArray[j]);
				}
			}
		}

		CurrentArrayStartingIndex = CurrentArrayEndingIndex;
		CurrentArrayEndingIndex = Result.Num();
	}

	Result.RemoveAt(0);
	return Result;
}

TArray<FMatrixIndex> UMovementLogic::GetNeighbouringTiles(FMatrixIndex TileIndex)
{
	TArray<FMatrixIndex> Result;

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			FMatrixIndex CurrentIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ);
			FTileData CurrentTileData;
			if (CurrentIndex != TileIndex && CombatGridManagerRef->TryGetTileDataByIndex(CurrentIndex, CurrentTileData) && !CurrentTileData.bIsVoid
				&& CurrentTileData.TileHolder == nullptr)
			{
				Result.Add(CurrentIndex);
			}
		}
	}

	//lower level
	for (int x = -1; x <= 1; x++) 
	{
		for (int y = -1; y <= 1; y++)
		{
			FMatrixIndex CurrentIndex = FMatrixIndex(x, y, TileIndex.IndexZ - 1);
			FMatrixIndex ObstacleIndex = FMatrixIndex(x, y, TileIndex.IndexZ);
			FTileData TileDataOfCurrentIndex;
			FTileData TileDataOfPotentialObstacle;
			if (CombatGridManagerRef->TryGetTileDataByIndex(CurrentIndex, TileDataOfCurrentIndex) && !TileDataOfCurrentIndex.bIsVoid
				&& CombatGridManagerRef->TryGetTileDataByIndex(ObstacleIndex, TileDataOfPotentialObstacle) && TileDataOfPotentialObstacle.bIsVoid
				&& TileDataOfCurrentIndex.TileHolder == nullptr)
			{
				Result.Add(CurrentIndex);
			}
		}
	}

	//upper level
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			FMatrixIndex CurrentIndex = FMatrixIndex(x, y, TileIndex.IndexZ + 1);
			FMatrixIndex ObstacleIndex = TileIndex;
			ObstacleIndex.IndexZ++;
			FTileData TileDataOfCurrentIndex;
			FTileData TileDataOfPotentialObstacle;
			if (CombatGridManagerRef->TryGetTileDataByIndex(CurrentIndex, TileDataOfCurrentIndex) && !TileDataOfCurrentIndex.bIsVoid
				&& CombatGridManagerRef->TryGetTileDataByIndex(ObstacleIndex, TileDataOfPotentialObstacle) && TileDataOfPotentialObstacle.bIsVoid
				&& TileDataOfCurrentIndex.TileHolder == nullptr)
			{
				Result.Add(CurrentIndex);
			}
		}
	}

	return Result;
}

TArray<UPathNode*> UMovementLogic::GetNeighbouringPathNodes(UPathNode* CurrentNode, FMatrixIndex DestinationTile)
{
	TArray<UPathNode*> Result;
	TArray<FMatrixIndex> NeighbouringTiles = GetNeighbouringTiles(CurrentNode->TileIndex);

	for (int i = 0; i < NeighbouringTiles.Num(); i++)
	{
		float EstimatedValue = sqrt(pow(NeighbouringTiles[i].IndexX - DestinationTile.IndexX, 2) + pow(NeighbouringTiles[i].IndexY - DestinationTile.IndexY, 2) + pow(NeighbouringTiles[i].IndexZ - DestinationTile.IndexZ, 2));
		UPathNode* neighbor = NewObject<UPathNode>();
		neighbor->Initialize(NeighbouringTiles[i], EstimatedValue);
		Result.Add(neighbor);
	}

	return Result;
}

TArray<FMatrixIndex> UMovementLogic::GetPath(FMatrixIndex StartTile, FMatrixIndex EndTile)
{
	TArray<FMatrixIndex> Result;
	bool PathIsFound = false;
	TArray<UPathNode*> OpenList;
	TArray<UPathNode*> ClosedList;
	float EstimatedCost = sqrt(pow(StartTile.IndexX - EndTile.IndexX, 2) + pow(StartTile.IndexY - EndTile.IndexY, 2) + pow(StartTile.IndexZ - EndTile.IndexZ, 2));
	UPathNode* CurrentNode = NewObject<UPathNode>();
	CurrentNode->Initialize(StartTile, EstimatedCost);
	CurrentNode->SetCurrentCost(0.0);
	OpenList.Add(CurrentNode);

	while (OpenList.Num() > 0)
	{
		OpenList.Sort([](const UPathNode& A, const UPathNode& B) {
			return A < B;
		});
		CurrentNode = OpenList[0];
		if (CurrentNode->TileIndex == EndTile)
		{
			PathIsFound = true;
			break;
		}
		ClosedList.Add(CurrentNode);
		OpenList.RemoveAt(0);
		TArray<UPathNode*> Neighbours = GetNeighbouringPathNodes(CurrentNode, EndTile);

		for (int i = 0; i < Neighbours.Num(); i++)
		{
			bool ClosedListContains = false;
			bool OpenListContains = false;
			UPathNode* OpenListNodeRef = nullptr;

			for (int j = 0; j < ClosedList.Num(); j++)
			{
				if (ClosedList[j]->TileIndex == Neighbours[i]->TileIndex)
				{
					ClosedListContains = true;
					break;
				}
			}
			for (int j = 0; j < OpenList.Num(); j++)
			{
				if (OpenList[j]->TileIndex == Neighbours[i]->TileIndex)
				{
					OpenListContains = true;
					OpenListNodeRef = OpenList[j];
					break;
				}
			}

			if (!ClosedListContains && !OpenListContains)
			{
				Neighbours[i]->SetCurrentCost(CurrentNode->CurrentCost + 1);
				Neighbours[i]->PreviousNode = CurrentNode;
				OpenList.Add(Neighbours[i]);
			}
			else if (OpenListContains && Neighbours[i]->CurrentCost > (CurrentNode->CurrentCost + 1))
			{
				OpenListNodeRef->SetCurrentCost(CurrentNode->CurrentCost + 1);
				OpenListNodeRef->PreviousNode = CurrentNode;
			}
		}
	}

	if (PathIsFound)
	{
		TArray<FMatrixIndex> InvResult;

		while (CurrentNode->PreviousNode != nullptr)
		{
			InvResult.Add(CurrentNode->TileIndex);
		}

		for (int i = InvResult.Num() - 1; i >= 0; i--)
		{
			Result.Add(InvResult[i]);
		}

		return Result;
	}
	else
	{
		return Result;
	}
}