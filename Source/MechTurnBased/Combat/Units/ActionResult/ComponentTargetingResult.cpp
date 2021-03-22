// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentTargetingResult.h"

UComponentTargetingResult::UComponentTargetingResult()
{

}

void UComponentTargetingResult::Initialize(UGridObjectComponent* GridObjectComponentToSet)
{
	GridObjectComponent = GridObjectComponentToSet;
}

void UComponentTargetingResult::AddGridObjectComponentStateUpdate(UGridObjectComponent* GridObjCompRef)
{
	UGridObjectComponentStateUpdate* GridObjCompStateUpd = NewObject<UGridObjectComponentStateUpdate>();
	GridObjCompStateUpd->Initialize(GridObjCompRef);
}