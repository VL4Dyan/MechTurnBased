// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "SightDirection.generated.h"

UENUM(BlueprintType)
enum class ESightDirection : uint8 //default direction - north
{
	Direction_North = 0 UMETA(DisplayName = "North"),
	Direction_East = 1 UMETA(DisplayName = "East"),
	Direction_South = 2 UMETA(DisplayName = "South"),
	Direction_West = 3 UMETA(DisplayName = "West")
};
