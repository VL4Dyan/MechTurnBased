// Fill out your copyright notice in the Description page of Project Settings.


#include "GridObjectUpdate.h"

FGridObjectUpdate::FGridObjectUpdate()
{
	
}

FGridObjectUpdate::FGridObjectUpdate(EGridObjectUpdateType GridObjectUpdateTypeToSet, TArray<FVector> WorldLocationTargetsToSet, TArray<AGridObject*> AffectedGridObjectsToSet)
{
	VisualUpdateType = GridObjectUpdateTypeToSet;
	WorldLocationTargets = WorldLocationTargetsToSet;
	AffectedGridObjects = AffectedGridObjectsToSet;
}
