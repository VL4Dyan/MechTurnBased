// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GridObjects/GridObjectComponent.h"
#include "GridObjectComponentStateUpdate.h"
#include "TileDataUpdate.h"
#include "TargetingResult.h"
#include "ComponentTargetingResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UComponentTargetingResult : public UTargetingResult
{
	GENERATED_BODY()

public:
	UComponentTargetingResult();

	UFUNCTION()
		void Initialize(UGridObjectComponent* GridObjectComponentToSet);
	UFUNCTION()
		void AddGridObjectComponentStateUpdate(UGridObjectComponent* GridObjCompRef);

public:
	UPROPERTY(BlueprintReadOnly)
		UGridObjectComponent* GridObjectComponent;

	UPROPERTY(BlueprintReadOnly)
		TArray<UTileDataUpdate*> TileUpdates;
	UPROPERTY(BlueprintReadOnly)
		TArray<UGridObjectComponentStateUpdate*> GridObjectComponentUpdates;
};
