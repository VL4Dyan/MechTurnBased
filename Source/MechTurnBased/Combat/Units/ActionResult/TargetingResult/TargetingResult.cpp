// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingResult.h"
#include "../../MechComponent.h"

UTargetingResult::UTargetingResult()
{

}

void UTargetingResult::SetExecutorComponent(UMechComponent* ExecutorComponentToSet)
{
	ExecutorComponent = ExecutorComponentToSet;
}

void UTargetingResult::ExecuteContainedUpdates()
{
	for (UGridObjectComponentStateUpdate* GridObjCompStateUpd : GridObjectComponentUpdates)
	{
		GridObjCompStateUpd->ExecuteUpdate();
	}

	for (UTileDataUpdate* TileDataUpd : TileUpdates)
	{
		TileDataUpd->ExecuteUpdate();
	}

	ExecutorComponent->ExecuteAction(this);
}