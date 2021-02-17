// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGridManager.h"

UCombatGridManager::UCombatGridManager()
{

}

void UCombatGridManager::BuildGrid()
{
	for (int x = 0; x < ScanRangeX; x++)
	{
		GridMatrix.Add(TArray<TArray<FTileData>>());
		for (int y = 0; y < ScanRangeY; y++)
		{
			GridMatrix[x].Add(TArray<FTileData>());
			for (int z = 0; z < ScanRangeZ; z++)
			{
				GridMatrix[x][y].Add(FTileData(x * TileStep + TileStep / 2, y * TileStep + TileStep / 2, z * TileHeight));
			}
		}
	}
}

bool UCombatGridManager::TryGetTileDataByIndex(const FMatrixIndex& Index, FTileData& OutTileData)
{
	if (IsIndexInRange(Index))
	{
		OutTileData = GridMatrix[Index.IndexX][Index.IndexY][Index.IndexZ];
		return true;
	}
	else
	{
		return false;
	}
}

FMatrixIndex UCombatGridManager::ConvertCoordinatesToIndexes(const FVector& Coordinates)
{
	int IndexX, IndexY, IndexZ;
	IndexX = (int)Coordinates.X / TileStep;
	IndexY = (int)Coordinates.Y / TileStep;
	IndexZ = (int)(Coordinates.Z + 0.1 * TileStep) / TileStep;
	return FMatrixIndex(IndexX, IndexY, IndexZ);
}

bool UCombatGridManager::TryUpdateTileData(const FMatrixIndex& Index, FTileData TileData)
{
	if (IsIndexInRange(Index))
	{
		TileData.AbsoluteCoordinates = GridMatrix[Index.IndexX][Index.IndexY][Index.IndexZ].AbsoluteCoordinates;
		GridMatrix[Index.IndexX][Index.IndexY][Index.IndexZ] = TileData;
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::IsTileHolderInTileDataNull(FTileData TileData)
{
	if (TileData.TileHolder == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::TryGetUnoccupiedTileAroundSpawnPoint(FMatrixIndex SpawnPointIndex, FMatrixIndex& OutTileIndex)
{
	int Radius = 0;

	if (Radius < ScanRangeX) Radius = ScanRangeX;
	if (Radius < ScanRangeY) Radius = ScanRangeY;
	if (Radius < ScanRangeZ) Radius = ScanRangeZ;

	for (int r = 0; r < Radius; r++)
	{
		//each loop represents one of the sides of scanned volume

		//lower side
		for (int x = SpawnPointIndex.IndexX - r; x <= SpawnPointIndex.IndexX + r; x++)
		{
			int z = SpawnPointIndex.IndexZ - r;
			for (int y = SpawnPointIndex.IndexY - r; y <= SpawnPointIndex.IndexY + r; y++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (!GridMatrix[x][y][z].bIsVoid && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}

		//left side
		for (int y = SpawnPointIndex.IndexY - r; y <= SpawnPointIndex.IndexY + r; y++)
		{
			int x = SpawnPointIndex.IndexX - r;
			for (int z = SpawnPointIndex.IndexZ - r; z <= SpawnPointIndex.IndexZ + r; z++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}

		//right side
		for (int y = SpawnPointIndex.IndexY - r; y <= SpawnPointIndex.IndexY + r; y++)
		{
			int x = SpawnPointIndex.IndexX + r;
			for (int z = SpawnPointIndex.IndexZ - r; z <= SpawnPointIndex.IndexZ + r; z++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}

		//front side
		for (int x = SpawnPointIndex.IndexX - r; x <= SpawnPointIndex.IndexX + r; x++)
		{
			int y = SpawnPointIndex.IndexY - r;
			for (int z = SpawnPointIndex.IndexZ - r; z <= SpawnPointIndex.IndexZ + r; z++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}

		//back side
		for (int x = SpawnPointIndex.IndexX - r; x <= SpawnPointIndex.IndexX + r; x++)
		{
			int y = SpawnPointIndex.IndexY + r;
			for (int z = SpawnPointIndex.IndexZ - r; z <= SpawnPointIndex.IndexZ + r; z++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}

		//upper side
		for (int x = SpawnPointIndex.IndexX - r; x <= SpawnPointIndex.IndexX + r; x++)
		{
			int z = SpawnPointIndex.IndexZ + r;
			for (int y = SpawnPointIndex.IndexY - r; y <= SpawnPointIndex.IndexY + r; y++)
			{
				if (AreValuesInRange(x, y, z))
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
					{
						OutTileIndex = FMatrixIndex(x, y, z);
						return true;
					}
				}
			}
		}
	}

	return false;
}

/*bool UCombatGridManager::TryGetLocationsToMoveThrough(const FMatrixIndex& StartLocationIndexes, const FMatrixIndex& EndLocationIndexes, TArray<FVector>& OutVectorArray)
{
	TArray<FVector> Result;
	bool PathIsFound = false;
	TArray<UPathfindingNode*> OpenList;
	TArray<UPathfindingNode*> ClosedList;
	float EstimatedCost = sqrt(pow(StartLocationIndexes.IndexX - EndLocationIndexes.IndexX, 2) + pow(StartLocationIndexes.IndexY - EndLocationIndexes.IndexY, 2) + pow(StartLocationIndexes.IndexZ - EndLocationIndexes.IndexZ, 2));
	UPathfindingNode* CurrentNode = NewObject<UPathfindingNode>();
	CurrentNode->Initialize(StartLocationIndexes, EstimatedCost);
	CurrentNode->SetNewCurrentCost(0);
	OpenList.Add(CurrentNode);

	while (OpenList.Num() > 0)
	{
		OpenList.Sort([](const UPathfindingNode& A, const UPathfindingNode& B) {
			return A < B;
		});
		CurrentNode = OpenList[0];
		if (CurrentNode->Indexes == EndLocationIndexes)
		{
			PathIsFound = true;
			break;
		}
		ClosedList.Add(CurrentNode);
		OpenList.RemoveAt(0);
		TArray<UPathfindingNode*> Neighbors = GetNeighbors(CurrentNode, EndLocationIndexes);

		for (int i = 0; i < Neighbors.Num(); i++)
		{
			bool ClosedListContains = false;
			bool OpenListContains = false;

			for (int j = 0; j < ClosedList.Num(); j++)
			{
				if (ClosedList[j]->Indexes == Neighbors[i]->Indexes)
				{
					ClosedListContains = true;
					break;
				}
			}
			for (int j = 0; j < OpenList.Num(); j++)
			{
				if (OpenList[j]->Indexes == Neighbors[i]->Indexes)
				{
					OpenListContains = true;
					break;
				}
			}

			if (!ClosedListContains && !OpenListContains)
			{
				Neighbors[i]->SetNewCurrentCost(CurrentNode->CurrentCost + 1);
				Neighbors[i]->Previous = CurrentNode;
				OpenList.Add(Neighbors[i]);
			}
			else if (OpenListContains && Neighbors[i]->CurrentCost > (CurrentNode->CurrentCost + 1))
			{
				Neighbors[i]->SetNewCurrentCost(CurrentNode->CurrentCost + 1);
				Neighbors[i]->Previous = CurrentNode;
			}
		}
	}

	while (CurrentNode != nullptr && PathIsFound)
	{
		FTileData Temp;
		PathIsFound = TryGetTileDataByIndex(CurrentNode->Indexes, Temp);
		if (PathIsFound)
		{
			Result.Add(Temp.AbsoluteCoordinates);
		}
		else
		{
			break;
		}
		CurrentNode = CurrentNode->Previous;
	}

	TArray<FVector> ReversedResult;
	if (PathIsFound)
	{
		for (int i = Result.Num() - 1; i >= 0; i--)
		{
			ReversedResult.Add(Result[i]);
		}
	}

	OutVectorArray = ReversedResult;
	return PathIsFound;
}

TArray<UPathfindingNode*> UCombatGridManager::GetNeighbors(UPathfindingNode* CurrentNode, FMatrixIndex DestinationPoint)
{
	TArray<UPathfindingNode*> Neighbors;
	FMatrixIndex Centre = CurrentNode->Indexes;

	//upper level
	int z = Centre.IndexZ + 1;
	for (int x = Centre.IndexX - 1; x <= Centre.IndexX + 1; x++)
	{
		for (int y = Centre.IndexY - 1; y <= Centre.IndexY + 1; y++)
		{
			if (AreValuesInRange(x, y, z))
			{
				if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - DestinationPoint.IndexX, 2) + pow(y - DestinationPoint.IndexY, 2) + pow(z - DestinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndex(x, y, z), EstimatedValue);
					Neighbors.Add(neighbor);
				}
			}
		}
	}
	//middle level
	z = Centre.IndexZ;
	for (int x = Centre.IndexX - 1; x <= Centre.IndexX + 1; x++)
	{
		for (int y = Centre.IndexY - 1; y <= Centre.IndexY + 1; y++)
		{
			if (AreValuesInRange(x, y, z))
			{
				if (!(x == Centre.IndexX && y == Centre.IndexY && z == Centre.IndexZ) && GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - DestinationPoint.IndexX, 2) + pow(y - DestinationPoint.IndexY, 2) + pow(z - DestinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndex(x, y, z), EstimatedValue);
					Neighbors.Add(neighbor);
				}
			}
		}
	}
	//lower level
	z = Centre.IndexZ - 1;
	for (int x = Centre.IndexX - 1; x <= Centre.IndexX + 1; x++)
	{
		for (int y = Centre.IndexY - 1; y <= Centre.IndexY + 1; y++)
		{
			if (AreValuesInRange(x, y, z))
			{
				if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - DestinationPoint.IndexX, 2) + pow(y - DestinationPoint.IndexY, 2) + pow(z - DestinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndex(x, y, z), EstimatedValue);
					Neighbors.Add(neighbor);
				}
			}
		}
	}

	return Neighbors;
}*/

bool UCombatGridManager::SwapTileHolders(const FMatrixIndex& TileOneIndex, const FMatrixIndex& TileTwoIndex)
{
	bool FunctionSuccess = false;
	AGridObject* Temp = nullptr;
	FTileData TileOne;
	FTileData TileTwo;

	FunctionSuccess = TryGetTileDataByIndex(TileOneIndex, TileOne);
	FunctionSuccess = TryGetTileDataByIndex(TileTwoIndex, TileTwo);

	Temp = TileOne.TileHolder;
	TileOne.TileHolder = TileTwo.TileHolder;
	TileTwo.TileHolder = Temp;

	if (FunctionSuccess)
	{
		FunctionSuccess = TryUpdateTileData(TileOneIndex, TileOne);
		FunctionSuccess = TryUpdateTileData(TileTwoIndex, TileTwo);
	}

	return FunctionSuccess;
}

bool UCombatGridManager::IsIndexInRange(const FMatrixIndex& Index)
{
	if (Index.IndexX >= 0 && Index.IndexY >= 0 && Index.IndexZ >= 0 && Index.IndexX < ScanRangeX && Index.IndexY < ScanRangeY && Index.IndexZ < ScanRangeZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::AreValuesInRange(const int& IndexX, const int& IndexY, const int& IndexZ)
{
	if (IndexX >= 0 && IndexY >= 0 && IndexZ >= 0 && IndexX < ScanRangeX && IndexY < ScanRangeY && IndexZ < ScanRangeZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*TArray<FMatrixIndex> UCombatGridManager::GetReachableTileIndexesForWalker(FMatrixIndex UnitTileIndexes, int UnitMovingDistance)
{
	TArray<FMatrixIndex> OpenList;
	TArray<FMatrixIndex> ClosedList;
	int MovesLeft = UnitMovingDistance;
	OpenList.Add(UnitTileIndexes);

	while (OpenList.Num() > 0 && MovesLeft > 0)
	{
		MovesLeft--;

		//from lower to upper, excluding the center
		for (int z = OpenList[0].IndexZ - 1; z <= OpenList[0].IndexZ + 1; z++)
		{
			for (int x = OpenList[0].IndexX - 1; x <= OpenList[0].IndexX + 1; x++)
			{
				for (int y = OpenList[0].IndexY - 1; y <= OpenList[0].IndexY + 1; y++)
				{
					if (AreValuesInRange(x, y, z))
					{
						if (!(x == UnitTileIndexes.IndexX && y == UnitTileIndexes.IndexY) && GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
						{
							FMatrixIndex IndexesToCheck = FMatrixIndex(x, y, z);
							if (!ClosedList.Contains(IndexesToCheck) || !ClosedList.Contains(IndexesToCheck))
							{
								OpenList.Add(IndexesToCheck);
							}
						}
					}
				}
			}
		}
		ClosedList.Add(OpenList[0]);
		OpenList.RemoveAt(0);
	}

	if (ClosedList.Num() > 0)
	{
		ClosedList.RemoveAt(0);
	}

	return ClosedList;
}*/

void UCombatGridManager::GetTileMeasurments(float& OutTileWidthLength, float& OutTileHeight)
{
	OutTileWidthLength = TileStep;
	OutTileHeight = TileHeight;
}