// Fill out your copyright notice in the Description page of Project Settings.

#include "GridObjectComponentStateUpdate.h"

UGridObjectComponentStateUpdate::UGridObjectComponentStateUpdate()
{

}

void UGridObjectComponentStateUpdate::Initialize(UGridObjectComponent* GridObjCompToSet)
{
	if (GridObjCompToSet != nullptr)
	{
		bCorrectParameters = true;

		GridObjectComponent = GridObjCompToSet;

		GridObjectComponentStateReplacement = GridObjCompToSet->GetComponentState();
		OldGridObjectComponentState = GridObjectComponentStateReplacement;
	}
}

void UGridObjectComponentStateUpdate::SetGridObjectComponentStateReplacement(FGridObjectComponentState GridObjectComponentStateReplacementToSet)
{
	GridObjectComponentStateReplacement = GridObjectComponentStateReplacementToSet;
}

void UGridObjectComponentStateUpdate::ExecuteUpdate()
{
	if (bCorrectParameters)
	{
		GridObjectComponent->UpdateComponentState(GridObjectComponentStateReplacement);
	}
}

void UGridObjectComponentStateUpdate::GetCurrentComponentState(FGridObjectComponentState& OutGridObjCompState)
{
	OutGridObjCompState = OldGridObjectComponentState;
}

