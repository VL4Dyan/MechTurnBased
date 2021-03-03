// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUIWidgetLogic.h"

UCombatUIWidgetLogic::UCombatUIWidgetLogic()
{

}

bool UCombatUIWidgetLogic::TryGetCompRefBasedOnSignal(int Signal, UGridObjectComponent*& OutComponentRef)
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
}


