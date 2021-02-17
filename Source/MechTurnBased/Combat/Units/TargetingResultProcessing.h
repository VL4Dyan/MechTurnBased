// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionResult/TileDataUpdate.h"
#include "ActionResult/GridObjectComponentStateUpdate.h"
#include "ActionResult/ActionResult.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "../Grid/TileData.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "TargetingResultProcessing.generated.h"

UCLASS()
class MECHTURNBASED_API UTargetingResultProcessing : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static void ProcessTargetingResults(UActionResult* ActionTargetingResult, int Damage);
};
