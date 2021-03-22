// Fill out your copyright notice in the Description page of Project Settings.

#include "GridObjectComponentStateUpdate.h"

UGridObjectComponentStateUpdate::UGridObjectComponentStateUpdate()
{

}

void UGridObjectComponentStateUpdate::Initialize(UGridObjectComponent* GridObjCompRef)
{
	GridObjectComponent = GridObjCompRef;
}

