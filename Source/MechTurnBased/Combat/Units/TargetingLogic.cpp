// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingLogic.h"

UTargetingLogic::UTargetingLogic()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTargetingLogic::BeginPlay()
{
	Super::BeginPlay();

	CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();
	CombatGridManagerRef->GetTileMeasurments(TileWidthLength, TileHeight);
}

void UTargetingLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

	for (int i = 0; i < PotentiallyTargetableGridObjects.Num(); i++)
	{
		TArray<UGridObjectComponent*> TargetableMechComponents = GetTargetableGridObjectComponents(PositionToLookFrom, PotentiallyTargetableGridObjects[i]);
		if (TargetableMechComponents.Num() > 0)
		{
			for (int j = 0; j < TargetableMechComponents.Num(); j++)
			{
				UComponentTargetingResult* CompTargetingResult = Result->AddComponentTarget(TargetableMechComponents[j]);
			}
		}
	}

	return Result;
}

TArray<UGridObjectComponent*> UTargetingLogic::GetTargetableGridObjectComponents(FMatrixIndex PositionToLookFrom, AGridObject* TargetGridObject)
{
	TArray<UGridObjectComponent*> Result;
	TArray<FVector> RayStartingPoints;
	FTileData ExecutionerTileData;
	TArray<UGridObjectComponent*> GridObjectComponents;

	CombatGridManagerRef->TryGetTileDataByIndex(PositionToLookFrom, ExecutionerTileData);

	RayStartingPoints.Add(FVector(ExecutionerTileData.AbsoluteCoordinates.X, ExecutionerTileData.AbsoluteCoordinates.Y, ExecutionerTileData.AbsoluteCoordinates.Z + TileHeight / 2));
	RayStartingPoints.Append(GetExecutionerSidePoints(ExecutionerTileData.AbsoluteCoordinates, TargetGridObject->GetActorLocation()));

	for (int i = 0; i < GridObjectComponents.Num(); i++)
	{
		UBoxComponent* CollisionBox = GridObjectComponents[i]->GetCollisionRef();
		for (int j = 0; j < RayStartingPoints.Num(); j++)
		{
			if (!AnyObstaclesOnLine(RayStartingPoints[j], CollisionBox->GetComponentLocation(), CollisionBox))
			{
				Result.Add(GridObjectComponents[i]);
				break;
			}
		}
	}

	return Result;
}

bool UTargetingLogic::AnyObstaclesOnLine(FVector StartingPoint, FVector EndingPoint, UPrimitiveComponent* PrimitiveComponent)
{
	FHitResult Hit;
	GetWorld()->SweepSingleByChannel(Hit, StartingPoint, EndingPoint, FQuat(), CollisionChannel, FCollisionShape::MakeSphere(TraceSphereRadius));

	if (Hit.Component != PrimitiveComponent && Hit.Component != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TArray <FVector> UTargetingLogic::GetExecutionerSidePoints(FVector ExecutionerCentre, FVector TargetCentre)
{
	TArray<FVector> Result;
	float currX, currY;

	float D = 4 * pow(ExecutionerCentre.X, 2) - 4 * (TileWidthLength / 3) / (1 + pow(TargetCentre.X - ExecutionerCentre.X, 2) / pow(TargetCentre.Y - ExecutionerCentre.Y, 2));

	currX = (2 * ExecutionerCentre.X - sqrt(D)) / 2;
	currY = ExecutionerCentre.Y - ((TargetCentre.X - ExecutionerCentre.X) * (currX - ExecutionerCentre.X) / (TargetCentre.Y - ExecutionerCentre.Y));
	Result.Add(FVector(currX, currY, ExecutionerCentre.Z + TileHeight / 2));

	currX = (2 * ExecutionerCentre.X + sqrt(D)) / 2;
	currY = ExecutionerCentre.Y - ((TargetCentre.X - ExecutionerCentre.X) * (currX - ExecutionerCentre.X) / (TargetCentre.Y - ExecutionerCentre.Y));
	Result.Add(FVector(currX, currY, ExecutionerCentre.Z + TileHeight / 2));

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