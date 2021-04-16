// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingLogic.h"

UTargetingLogic::UTargetingLogic()
{

}

void UTargetingLogic::SetTargetsInActionResultViaLineTrace(UActionResult* ActionResultToProcess, FMatrixIndex PositionToLookFrom, int Range)
{
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

	for (AGridObject* GridObj : PotentiallyTargetableGridObjects)
	{
		TArray<UGridObjectComponent*> TargetableGridObjectComponents = GetTargetableGridObjectComponents(PositionToLookFrom, GridObj, Range);

		if (TargetableGridObjectComponents.Num() > 0)
		{
			UGridObjectTargetingResult* GridObjTargetingRes = ActionResultToProcess->AddGridObjectTarget(GridObj);

			for (UGridObjectComponent* GridObjComp : TargetableGridObjectComponents)
			{
				UComponentTargetingResult* CompTargetingResult = GridObjTargetingRes->AddComponentTarget(GridObjComp);
			}
		}
	}
}

TArray<UGridObjectComponent*> UTargetingLogic::GetTargetableGridObjectComponents(FMatrixIndex PositionToLookFrom, AGridObject* TargetGridObject, int Range)
{
	TArray<UGridObjectComponent*> Result;
	FTileData ExecutionerTileData;
	TArray<UGridObjectComponent*> GridObjectComponents;

	CombatGridManagerRef->TryGetTileDataByIndex(PositionToLookFrom, ExecutionerTileData);

	GridObjectComponents = TargetGridObject->GetGridObjectComponents();

	for (UGridObjectComponent* GridObjComp : GridObjectComponents)
	{
		UBoxComponent* CollisionBox = GridObjComp->GetCollisionRef();
		TArray<FVector> RayStartingPoints;
		FVector ExecutionerCentrePoint = FVector(ExecutionerTileData.AbsoluteCoordinates.X, ExecutionerTileData.AbsoluteCoordinates.Y, ExecutionerTileData.AbsoluteCoordinates.Z + TileHeight);
		int DistanceToComp;

		RayStartingPoints.Add(ExecutionerCentrePoint);
		RayStartingPoints.Append(GetExecutionerSidePoints(ExecutionerTileData.AbsoluteCoordinates, TargetGridObject->GetActorLocation()));

		DistanceToComp = GetDistanceBetweenPoints(ExecutionerCentrePoint, CollisionBox->GetComponentLocation()) / TileWidthLength;

		if (DistanceToComp <= Range)
		{
			for (int j = 0; j < RayStartingPoints.Num(); j++)
			{
				if (!AnyObstaclesOnLine(RayStartingPoints[j], CollisionBox->GetComponentLocation(), CollisionBox, ExecutionerTileData.TileHolder))
				{
					Result.Add(GridObjComp);
					break;
				}
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

float UTargetingLogic::GetDistanceBetweenPoints(FVector PointOne, FVector PointTwo)
{
	float Result;

	Result = sqrt(pow(PointOne.X - PointTwo.X, 2) + pow(PointOne.Y - PointTwo.Y, 2) + pow(PointTwo.Z - PointTwo.Z, 2));

	return Result;
}