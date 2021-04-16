// Fill out your copyright notice in the Description page of Project Settings.

#include "GridObject.h"

AGridObject::AGridObject()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGridObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGridObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

EGridObjectType AGridObject::GetGridObjectType()
{
	return GridObjectType;
}

TArray<FMatrixIndex> AGridObject::GetOccupiedTiles()
{
	return OccupiedTiles;
}

bool AGridObject::TryToFall()
{
	return false;
}

TArray<UGridObjectComponent*> AGridObject::GetGridObjectComponents()
{
	TArray<UGridObjectComponent*> Result;

	return Result;
}

bool AGridObject::TryGetGridObjectTileIndex(FMatrixIndex& OutTileIndex)
{
	OutTileIndex = FMatrixIndex(0, 0, 0);

	return false;
}

void AGridObject::ApplyEnvironmentalDamage(FMatrixIndex IndexOfAffectedTile, int Dmg)
{

}

TArray<UGridObjectComponent*> AGridObject::GetGridObjectComponentsOccupyingTileIndex(FMatrixIndex TileIndex)
{
	TArray<UGridObjectComponent*> Result;
	return Result;
}

TArray<UActionResult*> AGridObject::GetActionResultArray()
{
	TArray<UActionResult*> Result;

	return Result;
}