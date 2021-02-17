// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentTargetingResult.h"

UComponentTargetingResult::UComponentTargetingResult()
{

}

void UComponentTargetingResult::Initialize(UGridObjectComponent* GridObjectComponentToSet)
{
	GridObjectComponent = GridObjectComponentToSet;
}