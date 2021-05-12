// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementMechComponent.h"
#include "../../GridObjects/GridObject.h"

UMovementMechComponent::UMovementMechComponent()
{

}

FCombatUnitSize UMovementMechComponent::GetRelativeUnitSize()
{
	FCombatUnitSize RelativeSize = UnitSize;

	if (UnitViewDirection == ESightDirection::Direction_West || UnitViewDirection == ESightDirection::Direction_East)
	{
		RelativeSize.XLength = UnitSize.YWidth;
		RelativeSize.YWidth = UnitSize.XLength;
	}

	return RelativeSize;
}

void UMovementMechComponent::ExecuteAction(UTargetingResult* TargetingResult)
{
	if (TargetingResult->IsA<UTileTargetingResult>())
	{
		UTileTargetingResult* TileTargetingResult = Cast<UTileTargetingResult>(TargetingResult);

		TArray<FMatrixIndex> PathOfTiles = MovementLogicRef->GetPath(GridObjectComponentOwner, UnitViewDirection, UnitSize, UnitTileIndex, TileTargetingResult->TileIndex);
		FMatrixIndex TargetTileIndex = TileTargetingResult->TileIndex;
		TArray<FVector> Path;
		float TileWidthLength, TileHeight;
		CombatGridManagerRef->GetTileMeasurments(TileWidthLength, TileHeight);
		FCombatUnitSize RelativeSize = UnitSize;

		if (UnitViewDirection == ESightDirection::Direction_West || UnitViewDirection == ESightDirection::Direction_East)
		{
			RelativeSize.XLength = UnitSize.YWidth;
			RelativeSize.YWidth = UnitSize.XLength;
		}

		for (FMatrixIndex TileIndex : PathOfTiles)
		{
			float x, y, z;
			x = (TileIndex.IndexX * TileWidthLength - TileWidthLength / 2) - (TileWidthLength * (RelativeSize.XLength - 1));
			y = (TileIndex.IndexY * TileWidthLength - TileWidthLength / 2) - (TileWidthLength * (RelativeSize.YWidth - 1));
			z = TileIndex.IndexZ * TileHeight;

			Path.Add(FVector(x, y, z));
		}

		for (int x = 0; x < RelativeSize.XLength; x++)
		{
			for (int y = 0; y < RelativeSize.YWidth; y++)
			{
				for (int z = 0; z < RelativeSize.ZHeight; z++)
				{
					FMatrixIndex TileIndex = FMatrixIndex(UnitTileIndex.IndexX - x, UnitTileIndex.IndexY - y, UnitTileIndex.IndexZ + z);
					FTileData CurrTileData;

					CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, CurrTileData);
					CurrTileData.TileHolder = nullptr;
					CombatGridManagerRef->TryUpdateTileData(TileIndex, CurrTileData);
				}
			}
		}

		for (int x = 0; x < RelativeSize.XLength; x++)
		{
			for (int y = 0; y < RelativeSize.YWidth; y++)
			{
				for (int z = 0; z < RelativeSize.ZHeight; z++)
				{
					FMatrixIndex TileIndex = FMatrixIndex(TargetTileIndex.IndexX - x, TargetTileIndex.IndexY - y, TargetTileIndex.IndexZ + z);
					FTileData CurrTileData;

					CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, CurrTileData);
					CurrTileData.TileHolder = GridObjectComponentOwner;
					CombatGridManagerRef->TryUpdateTileData(TileIndex, CurrTileData);
				}
			}
		}

		FGridObjectUpdate GridObjectUpdate = FGridObjectUpdate();

		GridObjectComponentOwner->AddGridObjectUpdate(GridObjectUpdate);
	}
}

void UMovementMechComponent::RespondToPush(ESightDirection PushDirection, int Power)
{
	FCombatUnitSize RelativeSize = GetRelativeUnitSize();

	int XAxisModifier = 0, YAxisModifier = 0, XOffset = 0, YOffset = 0;
	switch (PushDirection)
	{
	case ESightDirection::Direction_North:
		XAxisModifier = 1;
		break;
	case ESightDirection::Direction_South:
		XAxisModifier = -1;
		XOffset = 1 - RelativeSize.XLength;
		break;
	case ESightDirection::Direction_East:
		YAxisModifier = 1;
		break;
	case ESightDirection::Direction_West:
		YAxisModifier = -1;
		YOffset = 1 - RelativeSize.YWidth;
		break;
	}


	FMatrixIndex StartingIndexOfCurrentlyCheckedZoneOfTiles = UnitTileIndex;
	for (int i = 0; i < Power; i++)
	{
		bool bBlocked = false;

		StartingIndexOfCurrentlyCheckedZoneOfTiles.IndexX += (XAxisModifier + XOffset);
		StartingIndexOfCurrentlyCheckedZoneOfTiles.IndexY += (YAxisModifier + YOffset);

		if (PushDirection == ESightDirection::Direction_West || PushDirection == ESightDirection::Direction_East)
		{
			for (int j = 0; j < RelativeSize.XLength; j++)
			{
				FMatrixIndex TileIndexOfCheckedRow = StartingIndexOfCurrentlyCheckedZoneOfTiles;
				TileIndexOfCheckedRow.IndexX -= j;
				FTileData TileDataToCheck;
				if (!CombatGridManagerRef->TryGetTileDataByIndex(TileIndexOfCheckedRow, TileDataToCheck) || !TileDataToCheck.bIsVoid || TileDataToCheck.TileHolder != nullptr)
				{
					bBlocked = true;
					break;
				}
			}
		}
		else
		{
			for (int j = 0; j < RelativeSize.YWidth; j++)
			{
				FMatrixIndex TileIndexOfCheckedRow = StartingIndexOfCurrentlyCheckedZoneOfTiles;
				TileIndexOfCheckedRow.IndexY -= j;
				FTileData TileDataToCheck;
				if (!CombatGridManagerRef->TryGetTileDataByIndex(TileIndexOfCheckedRow, TileDataToCheck) || !TileDataToCheck.bIsVoid || TileDataToCheck.TileHolder != nullptr)
				{
					bBlocked = true;
					break;
				}
			}
		}

		//To be continued: there are no "pushing" components yet and TryToFall() won't rely on this method
	}
}

bool UMovementMechComponent::TryToFall()
{
	bool Result = false;
	bool PlacementOutOfBounds = false;
	FMatrixIndex CurrentUnitTileIndex = UnitTileIndex;
	TArray<FMatrixIndex> IndexesOfCurrentObstacles;
	FCombatUnitSize RelativeSize = GetRelativeUnitSize();

	while (CheckIfUnitShouldFall(CurrentUnitTileIndex, RelativeSize, IndexesOfCurrentObstacles, PlacementOutOfBounds))
	{
		if (PlacementOutOfBounds)
		{
			FGridObjectUpdate GridObjectUpdate = FGridObjectUpdate();

			GridObjectComponentOwner->AddGridObjectUpdate(GridObjectUpdate);
			break;
		}

		//Any building component creating a platform for this unit gets immediately destroyed.
		//If any static platform (formed by map pieces) is supporting this unit, the unit shifts towards the way with the least amount of affected static platforms.

		bool AnyUnbreakableObstacle = false;
		TArray<AGridObject*> CrushedGridObjects;
		int XAxisWeight = 0, YAxisWeight = 0;
		float CentreX, CentreY;
		CentreX = CurrentUnitTileIndex.IndexX - ((float)RelativeSize.XLength / 2 - 0.5);
		CentreY = CurrentUnitTileIndex.IndexY - ((float)RelativeSize.YWidth / 2 - 0.5);

		for (FMatrixIndex TileIndex : IndexesOfCurrentObstacles)
		{
			FTileData CheckedTileData;

			if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, CheckedTileData))
			{
				if (!CheckedTileData.bIsVoid && CheckedTileData.TileHolder == nullptr)
				{
					AnyUnbreakableObstacle = true;

					if (TileIndex.IndexX > CentreX)
					{
						XAxisWeight++;
					}
					else
					{
						if (TileIndex.IndexX < CentreX)
						{
							XAxisWeight--;
						}
					}

					if (TileIndex.IndexY > CentreY)
					{
						YAxisWeight++;
					}
					else
					{
						if (TileIndex.IndexY < CentreY)
						{
							YAxisWeight--;
						}
					}
				}
				else
				{
					if (!CrushedGridObjects.Contains(CheckedTileData.TileHolder))
					{
						CrushedGridObjects.Add(CheckedTileData.TileHolder);
					}
				}
			}
		}

		for (AGridObject* GridObjRef : CrushedGridObjects)
		{
			if (!GridObjRef->TryToCrush(CurrentUnitTileIndex, RelativeSize))
			{
				AnyUnbreakableObstacle = true;
			}
		}

		FMatrixIndex CurrentTileIndexUpd;

		if (AnyUnbreakableObstacle)
		{
			if (TryGetShiftedUnitTileIndex(CurrentUnitTileIndex, RelativeSize, XAxisWeight, YAxisWeight, CurrentTileIndexUpd))
			{
				CurrentUnitTileIndex = CurrentTileIndexUpd;
			}
			else
			{
				FGridObjectUpdate GridObjectUpdate = FGridObjectUpdate();

				GridObjectComponentOwner->AddGridObjectUpdate(GridObjectUpdate);
			}
		}
		else
		{
			CurrentUnitTileIndex.IndexZ--;
		}
	}

	return Result;
}

bool UMovementMechComponent::TryAnchorUnitToTile(FMatrixIndex TileIndex)
{
	FCombatUnitSize RelativeSize = GetRelativeUnitSize();

	bool bIsTileAcceptable = true;

	for (int x = 0; x < RelativeSize.XLength; x++)
	{
		for (int y = 0; y < RelativeSize.YWidth; y++)
		{
			for (int z = 0; z < RelativeSize.ZHeight; z++)
			{
				FTileData CurrentTileData;
				FMatrixIndex CurrentTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ + z);

				if (!CombatGridManagerRef->TryGetTileDataByIndex(CurrentTileIndex, CurrentTileData) || CurrentTileData.TileHolder != nullptr)
				{
					bIsTileAcceptable = false;
					break;
				}
			}

			if (!bIsTileAcceptable)
			{
				break;
			}
		}

		if (!bIsTileAcceptable)
		{
			break;
		}
	}

	if (bIsTileAcceptable)
	{
		for (int x = 0; x < RelativeSize.XLength; x++)
		{
			for (int y = 0; y < RelativeSize.YWidth; y++)
			{
				FTileData CurrentTileData;
				FMatrixIndex CurrentTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ - 1);

				if (!CombatGridManagerRef->TryGetTileDataByIndex(CurrentTileIndex, CurrentTileData) || CurrentTileData.bIsVoid)
				{
					bIsTileAcceptable = false;
					break;
				}
			}

			if (!bIsTileAcceptable)
			{
				break;
			}
		}
	}

	if (bIsTileAcceptable)
	{
		for (int x = 0; x < RelativeSize.XLength; x++)
		{
			for (int y = 0; y < RelativeSize.YWidth; y++)
			{
				for (int z = 0; z < RelativeSize.ZHeight; z++)
				{
					FTileData CurrentTileData;
					FMatrixIndex CurrentTileIndex = FMatrixIndex(TileIndex.IndexX - x, TileIndex.IndexY - y, TileIndex.IndexZ + z);

					if (CombatGridManagerRef->TryGetTileDataByIndex(CurrentTileIndex, CurrentTileData))
					{
						CurrentTileData.TileHolder = GridObjectComponentOwner;
						CombatGridManagerRef->TryUpdateTileData(CurrentTileIndex, CurrentTileData);
					}
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool UMovementMechComponent::CheckIfUnitShouldFall(FMatrixIndex CurrentUnitTileIndex, FCombatUnitSize RelativeUnitSize, TArray<FMatrixIndex>& OutObstacleTileIndexes, bool& OutPlacementOutOfBounds)
{
	bool Result = false;
	TArray<FMatrixIndex> IndexesOfCurrentObstacles;
	int PlatformsCount = 0;

	//Checking if enough platforms support the unit ("unit part" there is any tile occupied by lower body of the unit).
	for (int x = 0; x < RelativeUnitSize.XLength; x++)
	{
		for (int y = 0; y < RelativeUnitSize.YWidth; y++)
		{
			FMatrixIndex CurrentlyCheckedTileIndex = CurrentUnitTileIndex;
			CurrentlyCheckedTileIndex.IndexX -= x;
			CurrentlyCheckedTileIndex.IndexY -= y;
			CurrentlyCheckedTileIndex.IndexZ -= 1;

			FTileData CurrentlyCheckedTileData;
			if (CombatGridManagerRef->TryGetTileDataByIndex(CurrentlyCheckedTileIndex, CurrentlyCheckedTileData))
			{
				if (!CurrentlyCheckedTileData.bIsVoid)
				{
					PlatformsCount++;
					IndexesOfCurrentObstacles.Add(CurrentlyCheckedTileIndex);
				}
				else
				{
					if (CurrentlyCheckedTileData.TileHolder != nullptr)
					{
						IndexesOfCurrentObstacles.Add(CurrentlyCheckedTileIndex);
					}
				}
			}
			else
			{
				OutPlacementOutOfBounds = true;
				OutObstacleTileIndexes = IndexesOfCurrentObstacles;
				Result = true;

				return Result;
			}
		}
	}

	float SupportedToUnsupportedUnitPartsRatio = (float)PlatformsCount / ((float)RelativeUnitSize.XLength * (float)RelativeUnitSize.YWidth);

	if (SupportedToUnsupportedUnitPartsRatio <= 0.5)
	{
		Result = true;
	}

	OutObstacleTileIndexes = IndexesOfCurrentObstacles;
	return Result;
}

bool UMovementMechComponent::TryGetShiftedUnitTileIndex(FMatrixIndex CurrentUnitTileIndex, FCombatUnitSize RelativeUnitSize, int XAxisWeight, int YAxisWeight, FMatrixIndex& OutNewUnitTileIndex)
{
	bool Result = false;

	int XAxisShiftPriority = 1, YAxisShiftPriority = 1;

	if (XAxisWeight > 0)
	{
		XAxisShiftPriority = -1;
	}
	if (YAxisWeight > 0)
	{
		YAxisShiftPriority = -1;
	}

	for (int XModifier = 1; XModifier > -2; XModifier -= 2)
	{
		for (int YModifier = 1; YModifier > -2; YModifier -= 2)
		{
			FMatrixIndex CheckedTileIndex = FMatrixIndex(CurrentUnitTileIndex.IndexX + (XAxisShiftPriority * XModifier),
				CurrentUnitTileIndex.IndexY + (YAxisShiftPriority * YModifier), CurrentUnitTileIndex.IndexZ);
			bool IsAreaFree = true;

			for (int x = 0; x < RelativeUnitSize.XLength; x++)
			{
				for (int y = 0; x < RelativeUnitSize.YWidth; y++)
				{
					for (int z = 0; z < RelativeUnitSize.ZHeight; z++)
					{
						FTileData CheckedTileData;
						FMatrixIndex CheckedPartOfTheArea = CheckedTileIndex;
						CheckedPartOfTheArea.IndexX -= x;
						CheckedPartOfTheArea.IndexY -= y;
						CheckedPartOfTheArea.IndexZ -= z;

						if (!CombatGridManagerRef->TryGetTileDataByIndex(CheckedPartOfTheArea, CheckedTileData) || !CheckedTileData.bIsVoid || CheckedTileData.TileHolder != nullptr)
						{
							IsAreaFree = false;
							break;
						}
					}

					if (!IsAreaFree)
					{
						break;
					}
				}

				if (!IsAreaFree)
				{
					break;
				}
			}

			if (IsAreaFree)
			{
				OutNewUnitTileIndex = CheckedTileIndex;
				return true;
			}
		}
	}

	return Result;
}