// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementMechComponent.h"

UMovementMechComponent::UMovementMechComponent()
{

}

void UMovementMechComponent::ExecuteAction(UTargetingResult* TargetingResult)
{
	if (TargetingResult->IsA<UTileTargetingResult>())
	{
		UTileTargetingResult* TileTargetingResult = Cast<UTileTargetingResult>(TargetingResult);

		TArray<FMatrixIndex> PathOfTiles = MovementLogicRef->GetPath(MechComponentOwner, UnitViewDirection, UnitSize, UnitTileIndex, TileTargetingResult->TileIndex);
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
					CurrTileData.TileHolder = MechComponentOwner;
					CombatGridManagerRef->TryUpdateTileData(TileIndex, CurrTileData);
				}
			}
		}

		MechComponentOwner->MoveAlongPath(Path);
	}
}

void UMovementMechComponent::RespondToPush(ESightDirection PushDirection, int Power)
{
	FCombatUnitSize RelativeSize = UnitSize;
	if (UnitViewDirection == ESightDirection::Direction_West || UnitViewDirection == ESightDirection::Direction_East)
	{
		RelativeSize.XLength = UnitSize.YWidth;
		RelativeSize.YWidth = UnitSize.XLength;
	}

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
	TArray<FMatrixIndex> IndexesOfExistingPlatforms;

	FCombatUnitSize RelativeSize = UnitSize;
	if (UnitViewDirection == ESightDirection::Direction_West || UnitViewDirection == ESightDirection::Direction_East)
	{
		RelativeSize.XLength = UnitSize.YWidth;
		RelativeSize.YWidth = UnitSize.XLength;
	}

	for (int x = 0; x < RelativeSize.XLength; x++)
	{
		for (int y = 0; y < RelativeSize.YWidth; y++)
		{
			FMatrixIndex CurrentlyCheckedTileIndex = UnitTileIndex;
			CurrentlyCheckedTileIndex.IndexX -= x;
			CurrentlyCheckedTileIndex.IndexY -= y;
			CurrentlyCheckedTileIndex.IndexZ -= 1;

			FTileData CurrentlyCheckedTileData;
			if (CombatGridManagerRef->TryGetTileDataByIndex(CurrentlyCheckedTileIndex, CurrentlyCheckedTileData) && !CurrentlyCheckedTileData.bIsVoid)
			{
				IndexesOfExistingPlatforms.Add(CurrentlyCheckedTileIndex);
			}
		}
	}

	if (IndexesOfExistingPlatforms.Num() == 0)
	{
		Result = true;
		bool bAnyPlatformFound = false;

		FMatrixIndex CurrentIndex = UnitTileIndex;
		CurrentIndex.IndexZ--;
		FTileData CurrentTileData;

		while (CombatGridManagerRef->TryGetTileDataByIndex(CurrentIndex, CurrentTileData))
		{
			for (int x = 0; x < RelativeSize.XLength; x++)
			{
				for (int y = 0; y < RelativeSize.YWidth; y++)
				{
					FMatrixIndex TileIndexOfThisLevel = CurrentIndex;
					TileIndexOfThisLevel.IndexX -= x;
					TileIndexOfThisLevel.IndexY -= y;

					if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndexOfThisLevel, CurrentTileData) && !CurrentTileData.bIsVoid)
					{
						bAnyPlatformFound = true;
						break;
					}
				}

				if (bAnyPlatformFound)
				{
					break;
				}
			}

			if (bAnyPlatformFound)
			{
				break;
			}
			else
			{
				CurrentIndex.IndexZ--;
			}
		}

		if (bAnyPlatformFound)
		{
			TArray<FVector> Path;

			FTileData PathTileData;
			CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, PathTileData);
			Path.Add(PathTileData.AbsoluteCoordinates);

			CombatGridManagerRef->TryGetTileDataByIndex(CurrentIndex, PathTileData);
			Path.Add(PathTileData.AbsoluteCoordinates);

			UnitTileIndex = CurrentIndex;
			MechComponentOwner->MoveAlongPath(Path);
		}
		else
		{
			for (int x = 0; x < RelativeSize.XLength; x++)
			{
				for (int y = 0; y < RelativeSize.YWidth; y++)
				{
					for (int z = 0; z < RelativeSize.ZHeight; z++)
					{
						FMatrixIndex TileIndexOfUpdatedTile = UnitTileIndex;
						TileIndexOfUpdatedTile.IndexX -= x;
						TileIndexOfUpdatedTile.IndexY -= y;
						TileIndexOfUpdatedTile.IndexZ += z;

						FTileData TileDataUpdate;
						CombatGridManagerRef->TryGetTileDataByIndex(TileIndexOfUpdatedTile, TileDataUpdate);
						TileDataUpdate.TileHolder = nullptr;
						CombatGridManagerRef->TryUpdateTileData(TileIndexOfUpdatedTile, TileDataUpdate);
					}
				}
			}

			MechComponentOwner->DestroyCombatUnit();
		}
	}

	return Result;
}

bool UMovementMechComponent::TryAnchorUnitToTile(FMatrixIndex TileIndex)
{
	FCombatUnitSize RelativeSize = UnitSize;
	if (UnitViewDirection == ESightDirection::Direction_West || UnitViewDirection == ESightDirection::Direction_East)
	{
		RelativeSize.XLength = UnitSize.YWidth;
		RelativeSize.YWidth = UnitSize.XLength;
	}

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
						CurrentTileData.TileHolder = MechComponentOwner;
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
