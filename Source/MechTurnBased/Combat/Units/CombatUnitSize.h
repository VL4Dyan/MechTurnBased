// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatUnitSize.generated.h"

USTRUCT(BlueprintType)
struct MECHTURNBASED_API FCombatUnitSize
{
	GENERATED_BODY()

public:
	FCombatUnitSize(int LengthToSet, int WidthToSet, int HeightToSet);
	FCombatUnitSize();

	//These parameters represent default unit's tile coverage (unit's view direction is "north" (+x))
	//Unit's tile index represents the farthest and lowest north-east tile covered by the unit
	UPROPERTY()
		int XLength;
	UPROPERTY()
		int YWidth;
	UPROPERTY()
		int ZHeight;
};
