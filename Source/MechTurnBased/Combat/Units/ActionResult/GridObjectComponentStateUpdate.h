// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GridObjects/GridObjectComponentState.h"
#include "../../GridObjects/GridObjectComponent.h"
#include "GridObjectComponentStateUpdate.generated.h"

UCLASS(Blueprintable)
class MECHTURNBASED_API UGridObjectComponentStateUpdate : public UObject
{
	GENERATED_BODY()

public:
	UGridObjectComponentStateUpdate();

	UPROPERTY()
		UGridObjectComponent* GridObjectComponent;
	UPROPERTY()
		FGridObjectComponentState GridObjectComponentStateReplacement;
};
