// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Class.h"
#include "../Grid/MatrixIndex.h"
#include "GridObjectComponentState.generated.h"

USTRUCT(BlueprintType)
struct FGridObjectComponentState
{
	GENERATED_BODY()

public:
	FGridObjectComponentState(int HullPointsToSet);
	FGridObjectComponentState();

	UPROPERTY()
		int HullPoints = 0;
};
