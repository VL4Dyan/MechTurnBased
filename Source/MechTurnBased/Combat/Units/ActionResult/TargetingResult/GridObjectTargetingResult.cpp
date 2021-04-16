// Fill out your copyright notice in the Description page of Project Settings.


#include "GridObjectTargetingResult.h"

UGridObjectTargetingResult::UGridObjectTargetingResult()
{

}

void UGridObjectTargetingResult::Initialize(AGridObject* GridObjectToSet)
{
	GridObject = GridObjectToSet;
}

UComponentTargetingResult* UGridObjectTargetingResult::AddComponentTarget(UGridObjectComponent* GridObjectComponentTarget)
{
	UComponentTargetingResult* ComponentTarget = NewObject<UComponentTargetingResult>();
	ComponentTarget->Initialize(GridObjectComponentTarget);

	ComponentTargetingResults.Add(ComponentTarget);

	return ComponentTarget;
}
