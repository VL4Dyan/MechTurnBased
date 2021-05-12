// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentTargetingResult.h"

UComponentTargetingResult::UComponentTargetingResult()
{

}

void UComponentTargetingResult::Initialize(UGridObjectComponent* GridObjectComponentToSet)
{
	GridObjectComponent = GridObjectComponentToSet;
}

UGridObjectComponentStateUpdate* UComponentTargetingResult::AddGridObjectComponentStateUpdate(UGridObjectComponent* GridObjCompRef)
{
	UGridObjectComponentStateUpdate* GridObjCompStateUpd = NewObject<UGridObjectComponentStateUpdate>();
	GridObjCompStateUpd->Initialize(GridObjCompRef);

	return GridObjCompStateUpd;
}