// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGridManager.h"


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
				GridMatrix[x][y].Add(FTileData(x * TileStep + TileStep / 2, y * TileStep + TileStep / 2, z * TileStep));
			}
		}
	}
}

bool UCombatGridManager::GetTileDataByIndex(const FMatrixIndexes& indexes, FTileData& tileDataOut)
{
	if (AreIndexesInRange(indexes))
	{
		tileDataOut = GridMatrix[indexes.IndexX][indexes.IndexY][indexes.IndexZ];
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::ConvertCoordinatesToIndexes(const FVector& coordinates, FMatrixIndexes& indexesOut)
{
	int IndexX, IndexY, IndexZ;
	IndexX = (int)coordinates.X / TileStep;
	IndexY = (int)coordinates.Y / TileStep;
	IndexZ = (int)(coordinates.Z + 0.1 * TileStep) / TileStep;
	if (IndexX >= 0 && IndexX < ScanRangeX && IndexY >= 0 && IndexY < ScanRangeY && IndexZ >= 0 && IndexZ < ScanRangeZ)
	{
		indexesOut = FMatrixIndexes(IndexX, IndexY, IndexZ);
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::UpdateTileData(const FMatrixIndexes& indexes, FTileData tileData)
{
	if (AreIndexesInRange(indexes))
	{
		GridMatrix[indexes.IndexX][indexes.IndexY][indexes.IndexZ] = tileData;
		return true;
	}
	else
	{
		return false;
	}
}

bool UCombatGridManager::AddCombatUnitOnBattlefield(ACombatUnit* combatUnit)
{
	FTileData tile;
	FMatrixIndexes unitSpawningPoint = CalculateSpawningPoint();
	bool bCanProceed = AreIndexesInRange(unitSpawningPoint);

	if (bCanProceed)
	{
		bCanProceed = GetTileDataByIndex(unitSpawningPoint, tile);
	}

	if (bCanProceed)
	{
		tile.TileHolder = combatUnit;
		combatUnit->SetActorLocation(tile.AbsoluteCoordinates);
		UpdateTileData(unitSpawningPoint, tile);

		FString msg = FString::FromInt(unitSpawningPoint.IndexX) + " " + FString::FromInt(unitSpawningPoint.IndexY) + " " + FString::FromInt(unitSpawningPoint.IndexZ);
		UE_LOG(LogTemp, Warning, TEXT("Spawning point: %s"), *msg);

		return true;
	}
	else
	{
		FString msg = FString::FromInt(unitSpawningPoint.IndexX) + " " + FString::FromInt(unitSpawningPoint.IndexY) + " " + FString::FromInt(unitSpawningPoint.IndexZ);
		UE_LOG(LogTemp, Warning, TEXT("Failed Spawning point: %s"), *msg);

		return false;
	}
}

bool UCombatGridManager::IsTileHolderInTileDataNull(FTileData tileData)
{
	if (tileData.TileHolder == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FMatrixIndexes UCombatGridManager::CalculateSpawningPoint()
{
	int radius = 0;

	if (radius < ScanRangeX) radius = ScanRangeX;
	if (radius < ScanRangeY) radius = ScanRangeY;
	if (radius < ScanRangeZ) radius = ScanRangeZ;

	for (int r = 0; r < radius; r++)
	{
		//each loop represents one of the sides of scanned volume

		//lower side
		for (int x = SpawningPoint.IndexX - r; x <= SpawningPoint.IndexX + r; x++)
		{
			int z = SpawningPoint.IndexZ - r;
			for (int y = SpawningPoint.IndexY - r; y <= SpawningPoint.IndexY + r; y++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (!GridMatrix[x][y][z].bIsVoid && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}

		//left side
		for (int y = SpawningPoint.IndexY - r; y <= SpawningPoint.IndexY + r; y++)
		{
			int x = SpawningPoint.IndexX - r;
			for (int z = SpawningPoint.IndexZ - r; z <= SpawningPoint.IndexZ + r; z++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}

		//right side
		for (int y = SpawningPoint.IndexY - r; y <= SpawningPoint.IndexY + r; y++)
		{
			int x = SpawningPoint.IndexX + r;
			for (int z = SpawningPoint.IndexZ - r; z <= SpawningPoint.IndexZ + r; z++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}

		//front side
		for (int x = SpawningPoint.IndexX - r; x <= SpawningPoint.IndexX + r; x++)
		{
			int y = SpawningPoint.IndexY - r;
			for (int z = SpawningPoint.IndexZ - r; z <= SpawningPoint.IndexZ + r; z++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}

		//back side
		for (int x = SpawningPoint.IndexX - r; x <= SpawningPoint.IndexX + r; x++)
		{
			int y = SpawningPoint.IndexY + r;
			for (int z = SpawningPoint.IndexZ - r; z <= SpawningPoint.IndexZ + r; z++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}

		//upper side
		for (int x = SpawningPoint.IndexX - r; x <= SpawningPoint.IndexX + r; x++)
		{
			int z = SpawningPoint.IndexZ + r;
			for (int y = SpawningPoint.IndexY - r; y <= SpawningPoint.IndexY + r; y++)
			{
				if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
				{
					if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == NULL)
					{
						return FMatrixIndexes(x, y, z);
					}
				}
			}
		}
	}

	return FMatrixIndexes(-1, -1, -1);
}

// Sets default values
UCombatGridManager::UCombatGridManager()
{

}

// Called when the game starts or when spawned
void UCombatGridManager::BeginPlay()
{
	Super::BeginPlay();
}

bool UCombatGridManager::GetLocationsToMoveThrough(const FMatrixIndexes& startLocationIndexes, const FMatrixIndexes& endLocationIndexes, TArray<FVector>& vectorArrayOut)
{
	TArray<FVector> Result;
	bool PathIsFound = false;
	TArray<UPathfindingNode*> OpenList;
	TArray<UPathfindingNode*> ClosedList;
	float EstimatedCost = sqrt(pow(startLocationIndexes.IndexX - endLocationIndexes.IndexX, 2) + pow(startLocationIndexes.IndexY - endLocationIndexes.IndexY, 2) + pow(startLocationIndexes.IndexZ - endLocationIndexes.IndexZ, 2));
	UPathfindingNode* CurrentNode = NewObject<UPathfindingNode>();
	CurrentNode->Initialize(startLocationIndexes, EstimatedCost);
	CurrentNode->SetNewCurrentCost(0);
	OpenList.Add(CurrentNode);

	while (OpenList.Num() > 0)
	{
		OpenList.Sort([](const UPathfindingNode& A, const UPathfindingNode& B) {
			return A < B;
		});
		CurrentNode = OpenList[0];
		if (CurrentNode->Indexes == endLocationIndexes)
		{
			PathIsFound = true;
			break;
		}
		ClosedList.Add(CurrentNode);
		OpenList.RemoveAt(0);
		TArray<UPathfindingNode*> Neighbors = GetNeighbors(CurrentNode, endLocationIndexes);

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
		PathIsFound = GetTileDataByIndex(CurrentNode->Indexes, Temp);
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

	vectorArrayOut = ReversedResult;
	return PathIsFound;
}

TArray<UPathfindingNode*> UCombatGridManager::GetNeighbors(UPathfindingNode* currentNode, FMatrixIndexes destinationPoint)
{
	TArray<UPathfindingNode*> Neighbors;
	FMatrixIndexes Centre = currentNode->Indexes;

	//upper level
	int z = Centre.IndexZ + 1;
	for (int x = Centre.IndexX - 1; x <= Centre.IndexX + 1; x++)
	{
		for (int y = Centre.IndexY - 1; y <= Centre.IndexY + 1; y++)
		{
			if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
			{
				if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - destinationPoint.IndexX, 2) + pow(y - destinationPoint.IndexY, 2) + pow(z - destinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndexes(x, y, z), EstimatedValue);
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
			if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ && !(x == Centre.IndexX && y == Centre.IndexY && z == Centre.IndexZ))
			{
				if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - destinationPoint.IndexX, 2) + pow(y - destinationPoint.IndexY, 2) + pow(z - destinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndexes(x, y, z), EstimatedValue);
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
			if (x >= 0 && y >= 0 && z >= 0 && x < ScanRangeX && y < ScanRangeY && z < ScanRangeZ)
			{
				if (GridMatrix[x][y][z].bIsVoid == false && GridMatrix[x][y][z].TileHolder == nullptr)
				{
					float EstimatedValue = sqrt(pow(x - destinationPoint.IndexX, 2) + pow(y - destinationPoint.IndexY, 2) + pow(z - destinationPoint.IndexZ, 2));
					UPathfindingNode* neighbor = NewObject<UPathfindingNode>();
					neighbor->Initialize(FMatrixIndexes(x, y, z), EstimatedValue);
					Neighbors.Add(neighbor);
				}
			}
		}
	}

	return Neighbors;
}

bool UCombatGridManager::SwapTileHolders(const FMatrixIndexes& tileOneIndexes, const FMatrixIndexes& tileTwoIndexes)
{
	bool FunctionSuccess = false;
	ACombatUnit* Temp = NULL;
	FTileData TileOne;
	FunctionSuccess = GetTileDataByIndex(tileOneIndexes, TileOne);
	FTileData TileTwo;
	FunctionSuccess = GetTileDataByIndex(tileTwoIndexes, TileTwo);
	Temp = TileOne.TileHolder;
	TileOne.TileHolder = TileTwo.TileHolder;
	TileTwo.TileHolder = Temp;
	FunctionSuccess = UpdateTileData(tileOneIndexes, TileOne);
	FunctionSuccess = UpdateTileData(tileTwoIndexes, TileTwo);

	return FunctionSuccess;
}

bool UCombatGridManager::AreIndexesInRange(const FMatrixIndexes& indexes)
{
	if (indexes.IndexX >= 0 && indexes.IndexY >= 0 && indexes.IndexZ >= 0 && indexes.IndexX < ScanRangeX && indexes.IndexY < ScanRangeY && indexes.IndexZ < ScanRangeZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}