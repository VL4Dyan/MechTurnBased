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

	// ...
}

UActionResult* UTargetingLogic::GetTargetsViaLineTrace(FMatrixIndex PositionToLookFrom, int Range)
{
	UActionResult* Result = NewObject<UActionResult>();
	TArray<FMatrixIndex> PotentiallyTargetableTiles;

	PotentiallyTargetableTiles.Append(GetTargetableIndexesInRange(PositionToLookFrom, Range, true));

	for (int i = 0; i < PotentiallyTargetableTiles.Num(); i++)
	{
		TArray<UMechComponent*> TargetableMechComponents = GetTargetableMechComponents(PositionToLookFrom, PotentiallyTargetableTiles[i]);
		if (TargetableMechComponents.Num() > 0)
		{
			Result->AddTileTarget(PotentiallyTargetableTiles[i]);

			for (int j = 0; j < TargetableMechComponents.Num(); j++)
			{
				Result->AddComponentTarget(PotentiallyTargetableTiles[i], TargetableMechComponents[j]);
				Result->TryCreateCompUpdate(TargetableMechComponents[j], PotentiallyTargetableTiles[i], TargetableMechComponents[j]);
			}
		}
	}

	return Result;
}

TArray<UMechComponent*> UTargetingLogic::GetTargetableMechComponents(FMatrixIndex PositionToLookFrom, FMatrixIndex TargetPosition)
{
	TArray<UMechComponent*> Result;
	TArray<FVector> RayStartingPoints;
	FTileData ExecutionerTileData, TargetTileData;
	CombatGridManagerRef->TryGetTileDataByIndex(PositionToLookFrom, ExecutionerTileData);
	CombatGridManagerRef->TryGetTileDataByIndex(TargetPosition, TargetTileData);
	ACombatUnit* EnemyUnit;
	TArray<UMechComponent*> UnitMechComponents;

	if (TargetTileData.TileHolder != nullptr)
	{
		if (TargetTileData.TileHolder->GetGridObjectType() == EGridObjectType::GOType_CombatUnit)
		{
			EnemyUnit = Cast<ACombatUnit>(TargetTileData.TileHolder);
			UnitMechComponents = EnemyUnit->GetMechComponentsHavingCollisionBoxes();
		}
	}

	RayStartingPoints.Add(FVector(ExecutionerTileData.AbsoluteCoordinates.X, ExecutionerTileData.AbsoluteCoordinates.Y, ExecutionerTileData.AbsoluteCoordinates.Z + TileHeight / 2));
	RayStartingPoints.Append(GetExecutionerSidePoints(ExecutionerTileData.AbsoluteCoordinates, TargetTileData.AbsoluteCoordinates));
	
	for (int i = 0; i < UnitMechComponents.Num(); i++)
	{
		UBoxComponent* CollisionBox = UnitMechComponents[i]->GetCollisionBoxRef();
		for (int j = 0; j < RayStartingPoints.Num(); j++)
		{
			if (!AnyObstaclesOnLine(RayStartingPoints[j], CollisionBox->GetComponentLocation(), CollisionBox))
			{
				Result.Add(UnitMechComponents[i]);
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

/*TArray<UTileTargetingResult*> UTargetingLogic::GetTargetsViaArcTrace(FMatrixIndex PositionToLookFrom, int Range)
{
	TArray<UTileTargetingResult*> Result;


	return Result;
}*/

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