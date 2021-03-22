// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingLogic.h"

UTargetingLogic::UTargetingLogic()
{

}

UActionResult* UTargetingLogic::GetTargetsViaLineTrace(FMatrixIndex PositionToLookFrom, int Range)
{
	UActionResult* Result = NewObject<UActionResult>();

	TArray<FMatrixIndex> PotentiallyTargetableTiles;
	PotentiallyTargetableTiles.Append(GetTargetableIndexesInRange(PositionToLookFrom, Range, true));

	TArray<AGridObject*> PotentiallyTargetableGridObjects;
	for (FMatrixIndex TileIndex : PotentiallyTargetableTiles)
	{
		FTileData TileData;
		CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, TileData);

		if (TileData.TileHolder != nullptr && !PotentiallyTargetableGridObjects.Contains(TileData.TileHolder))
		{
			PotentiallyTargetableGridObjects.Add(TileData.TileHolder);
		}
	}

	for (int i = 0; i < PotentiallyTargetableTiles.Num(); i++)
	{
		TArray<UGridObjectComponent*> TargetableGridObjectComponents = GetTargetableGridObjectComponents(PositionToLookFrom, PotentiallyTargetableTiles[i]);
		if (TargetableGridObjectComponents.Num() > 0)
		{
			TArray<FMatrixIndex> AffectedTiles;
			AffectedTiles.Add(PotentiallyTargetableTiles[i]);

			UTileTargetingResult* TileTargetingResult = Result->AddTileTarget(AffectedTiles);

			for (int j = 0; j < TargetableGridObjectComponents.Num(); j++)
			{
				UComponentTargetingResult* CompTargetingResult = TileTargetingResult->AddComponentTarget(TargetableGridObjectComponents[j]);

				CompTargetingResult->AddGridObjectComponentStateUpdate(TargetableGridObjectComponents[j]);
			}
		}
	}

	return Result;
}

TArray<UGridObjectComponent*> UTargetingLogic::GetTargetableGridObjectComponents(FMatrixIndex PositionToLookFrom, FMatrixIndex TargetTileIndex)
{
	TArray<UGridObjectComponent*> Result;
	TArray<FVector> RayStartingPoints;
	FTileData ExecutionerTileData, TargetTileData;
	TArray<UGridObjectComponent*> GridObjectComponents;

	CombatGridManagerRef->TryGetTileDataByIndex(PositionToLookFrom, ExecutionerTileData);
	CombatGridManagerRef->TryGetTileDataByIndex(TargetTileIndex, TargetTileData);

	RayStartingPoints.Add(FVector(ExecutionerTileData.AbsoluteCoordinates.X, ExecutionerTileData.AbsoluteCoordinates.Y, ExecutionerTileData.AbsoluteCoordinates.Z + TileHeight));
	RayStartingPoints.Append(GetExecutionerSidePoints(ExecutionerTileData.AbsoluteCoordinates, TargetTileData.AbsoluteCoordinates));

	if (TargetTileData.TileHolder != nullptr)
	{
		GridObjectComponents = TargetTileData.TileHolder->GetGridObjectComponentsOccupyingTileIndex(TargetTileIndex);
	}

	for (int i = 0; i < GridObjectComponents.Num(); i++)
	{
		UBoxComponent* CollisionBox = GridObjectComponents[i]->GetCollisionRef();
		for (int j = 0; j < RayStartingPoints.Num(); j++)
		{
			if (!AnyObstaclesOnLine(RayStartingPoints[j], CollisionBox->GetComponentLocation(), CollisionBox, ExecutionerTileData.TileHolder))
			{
				Result.Add(GridObjectComponents[i]);
				break;
			}
		}
	}

	return Result;
}

bool UTargetingLogic::AnyObstaclesOnLine(FVector StartingPoint, FVector EndingPoint, UPrimitiveComponent* ComponentToTrace, AGridObject* ActorToIgnore)
{
	FHitResult Hit;

	FCollisionQueryParams TraceCollisionParams = FCollisionQueryParams::DefaultQueryParam;
	TraceCollisionParams.AddIgnoredActor(ActorToIgnore);

	GetWorld()->SweepSingleByChannel(Hit, StartingPoint, EndingPoint, FQuat(), CollisionChannel, FCollisionShape::MakeSphere(TraceSphereRadius), TraceCollisionParams);

	if (Hit.Component == nullptr || Hit.Component != ComponentToTrace)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TArray<FVector> UTargetingLogic::GetExecutionerSidePoints(FVector ExecutionerCentre, FVector TargetCentre)
{
	TArray<FVector> Result;
	float DistanceToCentre = TileWidthLength / 3;
	float Height = TileHeight;
	float currX, currY;

	if (ExecutionerCentre.X != TargetCentre.X && ExecutionerCentre.Y != TargetCentre.Y)
	{
		float D = 4 * pow(ExecutionerCentre.X, 2) - 4 * (pow(ExecutionerCentre.X, 2) - (DistanceToCentre) / (1 + pow(TargetCentre.X - ExecutionerCentre.X, 2) / pow(TargetCentre.Y - ExecutionerCentre.Y, 2)));

		currX = (2 * ExecutionerCentre.X - sqrt(D)) / 2;
		currY = ExecutionerCentre.Y - ((TargetCentre.X - ExecutionerCentre.X) * (currX - ExecutionerCentre.X) / (TargetCentre.Y - ExecutionerCentre.Y));
		Result.Add(FVector(currX, currY, ExecutionerCentre.Z + Height));

		currX = (2 * ExecutionerCentre.X + sqrt(D)) / 2;
		currY = ExecutionerCentre.Y - ((TargetCentre.X - ExecutionerCentre.X) * (currX - ExecutionerCentre.X) / (TargetCentre.Y - ExecutionerCentre.Y));
		Result.Add(FVector(currX, currY, ExecutionerCentre.Z + Height));
	}
	else
	{
		if (ExecutionerCentre.X == TargetCentre.X)
		{
			Result.Add(FVector(ExecutionerCentre.X + DistanceToCentre, ExecutionerCentre.Y, Height));
			Result.Add(FVector(ExecutionerCentre.X - DistanceToCentre, ExecutionerCentre.Y, Height));
		}
		else
		{
			Result.Add(FVector(ExecutionerCentre.X, ExecutionerCentre.Y + DistanceToCentre, Height));
			Result.Add(FVector(ExecutionerCentre.X, ExecutionerCentre.Y + DistanceToCentre, Height));
		}
	}

	return Result;
}

TArray<FMatrixIndex> UTargetingLogic::GetTargetableIndexesInRange(FMatrixIndex PositionToLookFrom, int Range, bool bIgnoreTilesWithoutUnits)
{
	TArray<FMatrixIndex> Result;

	for (int x = PositionToLookFrom.IndexX - Range; x <= PositionToLookFrom.IndexX + Range; x++)
	{
		for (int y = PositionToLookFrom.IndexY - Range; y <= PositionToLookFrom.IndexY + Range; y++)
		{
			for (int z = PositionToLookFrom.IndexZ - Range; z <= PositionToLookFrom.IndexZ + Range; z++)
			{
				FMatrixIndex Indexes(x, y, z);
				FTileData TileData;
				if (Indexes != PositionToLookFrom && CombatGridManagerRef->TryGetTileDataByIndex(Indexes, TileData))
				{
					if (TileData.bIsVoid == false && (!bIgnoreTilesWithoutUnits || TileData.TileHolder != nullptr))
					{
						Result.Add(Indexes);
					}
				}
			}
		}
	}

	return Result;
}