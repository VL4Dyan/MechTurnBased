// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUIWidgetLogic.h"

UCombatUIWidgetLogic::UCombatUIWidgetLogic()
{

}

/*bool UCombatUIWidgetLogic::TryGetCompRefBasedOnSignal(int Signal, UGridObjectComponent*& OutComponentRef)
{
	TArray<UGridObjectComponent*> GridObjComps;

	if (GridObjectRef != nullptr)
	{
		GridObjComps = GridObjectRef->GetGridObjectComponents();
	}

	if (Signal >= 0 && Signal < GridObjComps.Num())
	{
		OutComponentRef = GridObjComps[Signal];
		return true;
	}

	OutComponentRef = nullptr;
	return false;
}*/

TArray<UActionResult*> UCombatUIWidgetLogic::GetActionResultArrayFromGridObject(AGridObject* GridObject)
{
	TArray<UActionResult*> Result;

	if (GridObject != nullptr)
	{
		Result = GridObject->GetActionResultArray();
	}

	return Result;
}

void UCombatUIWidgetLogic::ExtractActionResultsFromGridObject(AGridObject* GridObject)
{
	TArray<UActionResult*> ActionResultArrayToSort = GetActionResultArrayFromGridObject(GridObject);

	SortedActionResultArray.Empty();
	SortedActionResultArray.Add(nullptr);

	for (UActionResult* ActionResult : ActionResultArrayToSort)
	{
		FComponentDescription CompDescription = ActionResult->GetComponentDescription();

		if (CompDescription.ComponentType == EGridObjectCompType::CompType_Movement)
		{
			SortedActionResultArray[0] = ActionResult;
		}
		else if (CompDescription.ComponentType == EGridObjectCompType::CompType_Attack)
		{
			SortedActionResultArray.Add(ActionResult);
		}
	}
}

bool UCombatUIWidgetLogic::TryGetActionResultBasedOnSignal(int Signal, UActionResult*& OutActionResult)
{
	if (Signal >= 0 && Signal < SortedActionResultArray.Num() && SortedActionResultArray[Signal] != nullptr)
	{
		OutActionResult = SortedActionResultArray[Signal];
		return true;
	}
	else
	{
		OutActionResult = nullptr;
		return false;
	}
}