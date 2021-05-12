// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementLogic.h"

UMovementLogic::UMovementLogic()
{

}

void UMovementLogic::Initialize(UCombatGridManager* CombatGridManagerToSet)
{
	CombatGridManager = CombatGridManagerToSet;
}

void UMovementLogic::SetTargetsInActionResultViaMovementLogicProcessing(UActionResult* ActionResultToProcess, AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartTile, int Distance)
{
	TArray<FMatrixIndex> EndLocations = GetAllEndLocations(MovingGridObject, SightDirection, UnitSize, StartTile, Distance);

	for (FMatrixIndex TileIndex : EndLocations)
	{
		ActionResultToProcess->AddTileTarget(TileIndex);
	}
}

TArray<FMatrixIndex> UMovementLogic::GetAllEndLocations(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartingTile, int Distance)
{
	TArray<FMatrixIndex> Result;
	int MovesLeft = Distance;
	int CurrentArrayStartingIndex = 0, CurrentArrayEndingIndex = 0;
	Result.Add(StartingTile);
	CurrentArrayEndingIndex = Result.Num();

	FCombatUnitSize RelativeSize;
	if (SightDirection == ESightDirection::Direction_East || SightDirection == ESightDirection::Direction_West)
	{
		RelativeSize = FCombatUnitSize(UnitSize.YWidth, UnitSize.XLength, UnitSize.ZHeight);
	}
	else
	{
		RelativeSize = UnitSize;
	}

	while (MovesLeft > 0 && CurrentArrayStartingIndex != CurrentArrayEndingIndex)
	{
		MovesLeft--;

		for (int i = CurrentArrayStartingIndex; i < CurrentArrayEndingIndex; i++)
		{
			TArray<FMatrixIndex> TempIndexesArray = GetNeighbouringTiles(Result[i], MovingGridObject);

			for (int j = 0; j < TempIndexesArray.Num(); j++)
			{
				if (!Result.Contains(TempIndexesArray[j]))
				{
					bool bIsAreaFree = true;

					for (int x = 0; x < RelativeSize.XLength; x++)
					{
						for (int y = 0; y < RelativeSize.YWidth; y++)
						{
							for (int z = 0; z < RelativeSize.ZHeight; z++)
							{
								FTileData CurrTileData;
								FMatrixIndex CurrIndex = TempIndexesArray[j];
								CurrIndex.IndexX -= x;
								CurrIndex.IndexY -= y;
								CurrIndex.IndexZ += z;

								if (!(CombatGridManager->TryGetTileDataByIndex(CurrIndex, CurrTileData) && (CurrTileData.TileHolder == nullptr || CurrTileData.TileHolder == MovingGridObject)))
								{
									bIsAreaFree = false;
									break;
								}
							}
							if (!bIsAreaFree)
							{
								break;
							}
						}

						if (!bIsAreaFree)
						{
							break;
						}
					}

					if (bIsAreaFree)
					{
						Result.Add(TempIndexesArray[j]);
					}
				}
			}
		}

		CurrentArrayStartingIndex = CurrentArrayEndingIndex;
		CurrentArrayEndingIndex = Result.Num();
	}

	Result.RemoveAt(0);
	return Result;
}

TArray<FMatrixIndex> UMovementLogic::GetNeighbouringTiles(FMatrixIndex TileIndex, AGridObject* GridObjectToIgnore)
{
	TArray<FMatrixIndex> Result;

	//same level
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 || y == 0)
			{
				FMatrixIndex CheckedTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ);
				FMatrixIndex PlatformIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ - 1);
				FTileData CheckedTileData, PlatformTileData;

				if (CheckedTileIndex != TileIndex && CombatGridManager->TryGetTileDataByIndex(CheckedTileIndex, CheckedTileData) && CheckedTileData.bIsVoid
					&& (CheckedTileData.TileHolder == nullptr || CheckedTileData.TileHolder == GridObjectToIgnore)
					&& CombatGridManager->TryGetTileDataByIndex(PlatformIndex, PlatformTileData) && !PlatformTileData.bIsVoid)
				{
					Result.Add(CheckedTileIndex);
				}
			}
		}
	}

	//lower level
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 || y == 0)
			{
				FMatrixIndex CheckedTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ - 1);
				FMatrixIndex PlatformIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ - 2);
				FMatrixIndex PotentialObstacleIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ);
				FTileData CheckedTileData, PotentialObstacleTileData, PlatformTileData;
				if (CombatGridManager->TryGetTileDataByIndex(CheckedTileIndex, CheckedTileData) && CheckedTileData.bIsVoid
					&& (CheckedTileData.TileHolder == nullptr || CheckedTileData.TileHolder == GridObjectToIgnore)
					&& CombatGridManager->TryGetTileDataByIndex(PotentialObstacleIndex, PotentialObstacleTileData) && PotentialObstacleTileData.bIsVoid
					&& CombatGridManager->TryGetTileDataByIndex(PlatformIndex, PlatformTileData) && !PlatformTileData.bIsVoid)
				{
					Result.Add(CheckedTileIndex);
				}
			}
		}
	}

	//upper level
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 || y == 0)
			{
				FMatrixIndex CheckedTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ + 1);
				FMatrixIndex PlatformIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ);
				FMatrixIndex PotentialObstacleIndex = FMatrixIndex(TileIndex.IndexX, TileIndex.IndexY, TileIndex.IndexZ + 1);
				FTileData CheckedTileData, PotentialObstacleTileData, PlatformTileData;
				if (CombatGridManager->TryGetTileDataByIndex(CheckedTileIndex, CheckedTileData) && CheckedTileData.bIsVoid
					&& (CheckedTileData.TileHolder == nullptr || CheckedTileData.TileHolder == GridObjectToIgnore)
					&& CombatGridManager->TryGetTileDataByIndex(PotentialObstacleIndex, PotentialObstacleTileData) && PotentialObstacleTileData.bIsVoid
					&& CombatGridManager->TryGetTileDataByIndex(PlatformIndex, PlatformTileData) && !PlatformTileData.bIsVoid)
				{
					Result.Add(CheckedTileIndex);
				}
			}
		}
	}

	return Result;
}

TArray<UPathNode*> UMovementLogic::GetNeighbouringPathNodes(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, UPathNode* CurrentNode, FMatrixIndex DestinationTile)
{
	TArray<UPathNode*> Result;
	TArray<FMatrixIndex> NeighbouringTiles = GetNeighbouringTiles(CurrentNode->TileIndex, MovingGridObject);

	FCombatUnitSize RelativeSize;
	if (SightDirection == ESightDirection::Direction_East || SightDirection == ESightDirection::Direction_West)
	{
		RelativeSize = FCombatUnitSize(UnitSize.YWidth, UnitSize.XLength, UnitSize.ZHeight);
	}
	else
	{
		RelativeSize = UnitSize;
	}

	for (FMatrixIndex NeighbourTile : NeighbouringTiles)
	{
		bool bIsAreaFree = true;

		for (int x = 0; x < RelativeSize.XLength; x++)
		{
			for (int y = 0; y < RelativeSize.YWidth; y++)
			{
				for (int z = 0; z < RelativeSize.ZHeight; z++)
				{
					FTileData CurrTileData;
					FMatrixIndex CurrIndex = NeighbourTile;
					CurrIndex.IndexX -= x;
					CurrIndex.IndexY -= y;
					CurrIndex.IndexZ += z;

					if (!(CombatGridManager->TryGetTileDataByIndex(CurrIndex, CurrTileData) && (CurrTileData.TileHolder == nullptr || CurrTileData.TileHolder == MovingGridObject)))
					{
						bIsAreaFree = false;
						break;
					}
				}
				if (!bIsAreaFree)
				{
					break;
				}
			}

			if (!bIsAreaFree)
			{
				break;
			}
		}

		if (bIsAreaFree)
		{
			float EstimatedValue = sqrt(pow(NeighbourTile.IndexX - DestinationTile.IndexX, 2) + pow(NeighbourTile.IndexY - DestinationTile.IndexY, 2) + pow(NeighbourTile.IndexZ - DestinationTile.IndexZ, 2));
			UPathNode* neighbor = NewObject<UPathNode>();
			neighbor->Initialize(NeighbourTile, EstimatedValue);
			Result.Add(neighbor);
		}
	}

	return Result;
}

TArray<FMatrixIndex> UMovementLogic::GetPath(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartTile, FMatrixIndex EndTile)
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
		TArray<UPathNode*> Neighbours = GetNeighbouringPathNodes(MovingGridObject, SightDirection, UnitSize, CurrentNode, EndTile);

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