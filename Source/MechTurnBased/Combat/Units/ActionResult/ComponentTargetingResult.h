// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GridObjects/GridObjectComponent.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "ComponentTargetingResult.generated.h"

UCLASS(Blueprintable)
class MECHTURNBASED_API UComponentTargetingResult : public UObject
{
	GENERATED_BODY()

public:
	UComponentTargetingResult();

	UFUNCTION()
		void Initialize(UGridObjectComponent* GridObjectComponentToSet);

	UPROPERTY()
		UGridObjectComponent* GridObjectComponent;

	UPROPERTY()
		TArray<UTileDataUpdate*> TileUpdates;
	UPROPERTY()
		TArray<UGridObjectComponentStateUpdate*> MechComponentUpdates;
};
