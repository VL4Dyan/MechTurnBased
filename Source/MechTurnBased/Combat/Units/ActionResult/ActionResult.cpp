// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionResult.h"

UActionResult::UActionResult()
{

}

UTileTargetingResult* UActionResult::AddTileTarget(FMatrixIndex TargetTileIndex)
{
	UTileTargetingResult* TileTarget = NewObject<UTileTargetingResult>();
	TileTarget->Initialize(TargetTileIndex);

	TileTargetingResults.Add(TileTarget);
	
	return TileTarget;
}

UComponentTargetingResult* UActionResult::AddComponentTarget(UGridObjectComponent* GridObjectComponentRef)
{
	UComponentTargetingResult* ComponentTarget = NewObject<UComponentTargetingResult>();
	ComponentTarget->Initialize(GridObjectComponentRef);

	ComponentTargetingResults.Add(ComponentTarget);

	return ComponentTarget;
}
